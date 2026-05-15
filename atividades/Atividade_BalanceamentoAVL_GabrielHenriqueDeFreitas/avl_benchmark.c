#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left, *right;
} Node;

typedef struct ListNode {
    int key;
    struct ListNode *next;
} ListNode;

// Auxiliares AVL

int getHeight(Node *n)
{
    return n ? n->height : 0;
}

int getBalance(Node *n)
{
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *createNode(int key)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

// Inserção

Node *insertAVL(Node *node, int key)
{
    if (!node) {
        return createNode(key);
    }

    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    } else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node *insertBST(Node *node, int key)
{
    if (!node) {
        return createNode(key);
    }
    if (key < node->key) {
        node->left = insertBST(node->left, key);
    } else {
        node->right = insertBST(node->right, key);
    }
    return node;
}

ListNode *insertList(ListNode *head, int key)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->key = key;
    newNode->next = head;
    return newNode;
}

// Buscas

bool searchTree(Node *root, int key)
{
    if (!root) {
        return false;
    }
    if (root->key == key) {
        return true;
    }
    if (key < root->key) {
        return searchTree(root->left, key);
    }
    return searchTree(root->right, key);
}

bool searchList(ListNode *head, int key)
{
    while (head) {
        if (head->key == key) {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Validação

bool isBSTOrdered(Node *root, int *lastVal)
{
    if (!root) {
        return true;
    }
    if (!isBSTOrdered(root->left, lastVal)) {
        return false;
    }
    if (root->key <= *lastVal) {
        return false;
    }
    *lastVal = root->key;
    return isBSTOrdered(root->right, lastVal);
}

bool isAVLBalanced(Node *root)
{
    if (!root) {
        return true;
    }
    int bal = getBalance(root);
    if (bal < -1 || bal > 1) {
        return false;
    }
    return isAVLBalanced(root->left) && isAVLBalanced(root->right);
}

// Main
int main()
{
    srand(time(NULL));

    // Teste de Estresse
    printf("--- Teste de Estresse AVL ---\n");
    Node *stressRoot = NULL;
    for (int i = 0; i < 1000; i++) {
        stressRoot = insertAVL(stressRoot, rand() % 10000);
    }

    int lastVal = -1;
    printf("Propriedade BST: %s\n",
           isBSTOrdered(stressRoot, &lastVal) ? "OK" : "ERRO");
    printf("Propriedade AVL: %s\n\n",
           isAVLBalanced(stressRoot) ? "OK" : "ERRO");

    // Benchmark
    FILE *f = fopen("benchmark_resultados.csv", "w");
    if (!f) {
        return 1;
    }
    fprintf(f, "Elementos;AVL_Ticks;BST_Ticks;Lista_Ticks\n");

    for (int n = 100; n <= 10000; n += 500) {
        Node *avlRoot = NULL, *bstRoot = NULL;
        ListNode *listHead = NULL;

        for (int i = 1; i <= n; i++) {
            avlRoot = insertAVL(avlRoot, i);
            bstRoot = insertBST(bstRoot, i);
            listHead = insertList(listHead, i);
        }

        int exec = 10000;
        clock_t start;

        start = clock();
        for (int i = 0; i < exec; i++) {
            searchTree(avlRoot, n);
        }
        double tAVL = (double)(clock() - start);

        start = clock();
        for (int i = 0; i < exec; i++) {
            searchTree(bstRoot, n);
        }
        double tBST = (double)(clock() - start);

        start = clock();
        for (int i = 0; i < exec; i++) {
            searchList(listHead, 1);
        }
        double tList = (double)(clock() - start);

        fprintf(f, "%d;%.0f;%.0f;%.0f\n", n, tAVL, tBST, tList);
        printf("Processado N: %d\n", n);
    }

    fclose(f);
    return 0;
}
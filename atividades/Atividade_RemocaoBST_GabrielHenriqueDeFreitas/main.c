#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

Node *insert(Node *root, int value) {
    if (root == NULL) {
        Node *node = (Node *)malloc(sizeof(Node));
        node->data = value;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (value < root->data) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }

    return root;
}

Node *search(Node *root, int data) {
    Node *current = root;

    while (current != NULL) {
        if (data < current->data) {
            current = current->left;
        } else if (data > current->data) {
            current = current->right;
        } else {
            return current;
        }
    }
}

void inorder(Node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%i  ", root->data);
        inorder(root->right);
    }
}

int main() {
    int values[11] = {50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45};
    Node *root = NULL;

    for (int i = 0; i < 11; i++) {
        root = insert(root, values[i]);
    }

    inorder(root);
}
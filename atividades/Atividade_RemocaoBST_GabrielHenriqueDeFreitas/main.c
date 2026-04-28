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

Node *getSuccessor(Node *current) {
  current = current->right;

  while (current != NULL && current->left != NULL) {
    current = current->left;
  }

  return current;
}

Node *removeNode(Node *root, int value) {
  if (root == NULL) {
    return root;
  }

  if (root->data > value) {
    root->left = removeNode(root->left, value);
  } else if (root->data < value) {
    root->right = removeNode(root->right, value);
  } else {

    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    Node *successor = getSuccessor(root);
    root->data = successor->data;
    root->right = removeNode(root->right, successor->data);
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
  return NULL;
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

  // Inserção
  for (int i = 0; i < 11; i++) {
    root = insert(root, values[i]);
  }

  // Estado inicial
  printf("Arvore original (in-order):\n");
  inorder(root);
  printf("\n\n");

  // Remover 15
  root = removeNode(root, 15);
  printf("Apos remover 15:\n");
  inorder(root);
  printf("\n\n");

  // Remover 20
  root = removeNode(root, 20);
  printf("Apos remover 20:\n");
  inorder(root);
  printf("\n\n");

  // Remover 30
  root = removeNode(root, 30);
  printf("Apos remover 30:\n");
  inorder(root);
  printf("\n\n");

  // Remover 70
  root = removeNode(root, 70);
  printf("Apos remover 70:\n");
  inorder(root);
  printf("\n\n");

  // Remover 50
  root = removeNode(root, 50);
  printf("Apos remover 50 (estado final):\n");
  inorder(root);
  printf("\n");

  return 0;
}
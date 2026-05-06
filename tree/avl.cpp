#include <iostream>
using namespace std;

class AVL {
  class Node {
  public:
    int data;
    Node *left;
    Node *right;
    int getHeight;
  };
  Node *root = nullptr;

  int maxUtility(Node *current) {
    if (current->right == nullptr)
      return current->data;
    else
      return maxUtility(current->right);
  }

  int getHeight(Node *current) {
    if (current == nullptr)
      return 0;
    return current->getHeight;
  }

  Node *rightRotation(Node *current) {
    Node *new_Node = current->left;

    current->left = new_Node->right;

    new_Node->right = current;

    current->getHeight = 1 + max(getHeight(current->left), getHeight(current->right));
    new_Node->getHeight = 1 + max(getHeight(new_Node->left), getHeight(new_Node->right));

    return new_Node;
  }

  Node *leftRotation(Node *current) {
    Node *new_Node = current->right;

    current->right = new_Node->left;
    new_Node->left = current;

    current->getHeight = 1 + max(getHeight(current->left), getHeight(current->right));
    new_Node->getHeight = 1 + max(getHeight(new_Node->left), getHeight(new_Node->right));

    return new_Node;
  }

  Node *insert(Node *current, int value) {
    if (current == nullptr) {
      Node *new_Node = new Node;

      new_Node->data = value;

      new_Node->right = nullptr;
      new_Node->left = nullptr;

      new_Node->getHeight = 1;
      current = new_Node;
      return new_Node;
    }
    if (value < current->data)
      current->left = insert(current->left, value);
    else if (value > current->data)
      current->right = insert(current->right, value);

    current->getHeight = 1 + max(getHeight(current->left), getHeight(current->right));
    int balance = getHeight(current->left) - getHeight(current->right);

    if (balance > 1) {
      if (value > current->left->data) {
        current->left = leftRotation(current->left);
        return rightRotation(current);
      } else {
        return rightRotation(current);
      }
    } else if (balance < -1) {
      if (value < current->right->data) {
        current->right = rightRotation(current->right);
        return leftRotation(current);
      } else {
        return leftRotation(current);
      }
    }
    return current;
  }

public:
  void insert(int value) { root = insert(root, value); }
};
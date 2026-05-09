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
    Node *new_node = current->left;

    current->left = new_node->right;

    new_node->right = current;

    current->getHeight =
        1 + max(getHeight(current->left), getHeight(current->right));
    new_node->getHeight =
        1 + max(getHeight(new_node->left), getHeight(new_node->right));

    return new_node;
  }

  Node *leftRotation(Node *current) {
    Node *new_node = current->right;

    current->right = new_node->left;
    new_node->left = current;

    current->getHeight =
        1 + max(getHeight(current->left), getHeight(current->right));
    new_node->getHeight =
        1 + max(getHeight(new_node->left), getHeight(new_node->right));

    return new_node;
  }

  Node *insert(Node *current, int value) {
    if (current == nullptr) {
      Node *new_node = new Node;

      new_node->data = value;

      new_node->right = nullptr;
      new_node->left = nullptr;

      new_node->getHeight = 1;
      current = new_node;
      return new_node;
    }
    if (value < current->data)
      current->left = insert(current->left, value);
    else if (value > current->data)
      current->right = insert(current->right, value);

    current->getHeight =
        1 + max(getHeight(current->left), getHeight(current->right));
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

  void inorder(Node *root) {
    if (root != nullptr) {
      inorder(root->left);
      cout << root->data << " ";
      inorder(root->right);
    }
  }

public:
  void insert(int value) { root = insert(root, value); }
  void inorder() { inorder(root); }
};

int main() {
  AVL tree;
  tree.insert(10);
  tree.insert(20);
  tree.inorder();
}
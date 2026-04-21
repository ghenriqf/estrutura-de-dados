#include <iostream>
using namespace std;

class Node {
public:
  int data;

  Node *left;
  Node *right;

  Node(int data);
};

Node::Node(int data) {
  this->data = data;
  this->left = nullptr;
  this->right = nullptr;
}

class Tree {
private:
  Node *root;

  // inserção com recursividade
  Node *insert(Node *node, int data) {
    if (node == nullptr) {
      return new Node(data);
    }

    if (data < node->data) {
      node->left = insert(node->left, data);
    } else {
      node->right = insert(node->right, data);
    }

    return node;
  }

  void inorder(Node *node) {
    if (node != nullptr) {
      inorder(node->left);
      cout << node->data << " ";
      inorder(node->right);
    }
  }

  bool search(Node *node, int value) {
    if (node == nullptr) {
      return false;
    }

    if (node->data == value) {
      return true;
    }

    if (value < node->data) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

public:
  Tree() { this->root = nullptr; }
  ~Tree();
  // interfaces
  void insert(int data) { root = insert(root, data); }

  void inorder() {
    inorder(root);
    cout << endl;
  }

  bool search(int value) { return search(root, value); }
};
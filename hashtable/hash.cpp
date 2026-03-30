#include <iostream>
using namespace std;

class Node {
public:
  int key;
  string value;
  Node *next;

  Node(int key, string value) {
    this->key = key;
    this->value = value;
    this->next = nullptr;
  }
};

class HashTable {
private:
  static const int SIZE = 11;
  Node *table[SIZE];

  int hashFunction(int key) { return key % SIZE; }

public:
  HashTable() {
    for (int i = 0; i < SIZE; i++) {
      table[i] = nullptr;
    }
  }

  ~HashTable() {
    for (int i = 0; i < SIZE; i++) {
      Node *current = table[i];

      while (current != nullptr) {
        Node *temp = current;
        current = current->next;
        delete temp;
      }
    }
  }

  void put(int key, string value);
  string get(int key);
  void remove(int key);
};

void HashTable::put(int key, string value) {
  int index = hashFunction(key);

  Node *current = table[index];

  while (current != nullptr) {
    if (current->key == key) {
      current->value = value;
      return;
    }
    current = current->next;
  }

  Node *newNode = new Node(key, value);
  newNode->next = table[index];

  table[index] = newNode;
}

string HashTable::get(int key) {
  int index = hashFunction(key);

  Node *current = table[index];

  while (current != nullptr) {
    if (current->key == key) {
      return current->value;
    }
    current = current->next;
  }

  return "";
}
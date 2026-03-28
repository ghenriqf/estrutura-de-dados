#include <iostream>

// Implemetação simples de uma Lista Encadeada

class Node {
public:
  int data;
  Node *next;
  Node(int data) : data(data), next(nullptr) {}
};

class LinkedList {
private:
  Node *head;

public:
  LinkedList() : head(nullptr) {}

  // destrutor
  ~LinkedList() {
    Node *current = head;
    while (current != nullptr) {
      Node *temp = current;
      current = current->next;
      delete temp;
    }
  }

  // declaração dos métodos
  void insert(int value);
  void remove(int value);
  void print();
};

// implemetacão

void LinkedList::insert(int value) // método para inserir no início da lista
{
  // cria um novo nó que vai ser a cabeça da lista e altera o seu apontamento

  Node *newNode = new Node(value);

  newNode->next = head;
  head = newNode;
}

void LinkedList::remove(int value) {

  // se a lista não tiver nenhum valor inserido finaliza a função
  if (head == nullptr)
    return;

  // se tiver nós e a cabeça for o valor
  if (head->data == value) {
    Node *temp = head;
    head = head->next; // cabeça vai apontar para o próximo nó
    delete temp;
    return;
  }

  Node *current = head;

  while (current->next != nullptr && current->next->data != value) {
    current = current->next;
  }

  if (current->next != nullptr) {
    Node *temp = current->next;
    current->next = current->next->next;
    delete temp;
  }
}

void LinkedList::print() {
  // inicia um ponteiro para o primeiro nó da lista
  Node *current = head;

  // exibe o valor do nó enquanto o ponteiro não for nulo
  while (current != nullptr) {
    std::cout << current->data << " -> ";

    // vai para o próximo nó
    current = current->next;
  }
}

int main() {

  LinkedList list;

  list.insert(10);
  list.insert(20);
  list.insert(30);
  list.insert(40);

  list.print();

  list.remove(40);

  std::cout << "\n";

  list.print();

  return 0;
}
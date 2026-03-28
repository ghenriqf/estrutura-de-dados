#include <iostream>

// Implementação simples de uma Queue (Fila) utilizando array circular

class Queue {
private:
  int *arr;
  int capacity;
  int size;
  int front;
  int rear;

public:
  Queue(int capacity) {
    this->capacity = capacity;
    arr = new int[capacity];
    front = 0;
    /*
      inicializa o rear como -1 para que o primeiro elemento vá para a posição
      0 ao avançar o índice
    */
    rear = -1;
    size = 0;
  }

  // destrutor
  ~Queue() { delete[] arr; }

  // declaração dos métodos
  bool enqueue(int value);
  bool dequeue();
  int getFront();
  int getRear();
  bool isFull();
  bool isEmpty();
  void print();
};

// implementação

bool Queue::isFull() { return capacity == size; }

bool Queue::isEmpty() { return size == 0; }

int Queue::getFront() {
  if (isEmpty()) {
    return -1;
  }

  return arr[front];
}

int Queue::getRear() {
  if (isEmpty()) {
    return -1;
  }

  return arr[rear];
}

bool Queue::enqueue(int value) { // método para enfileirar
  if (isFull()) {
    return false;
  }

  /*
    o módulo faz o índice dar a volta ao chegar no final do array, mantendo-o
    sempre dentro dos limites
  */

  rear = (rear + 1) % capacity;
  arr[rear] = value;
  size++;

  return true;
}

bool Queue::dequeue() { // método para desenfileirar
  if (isEmpty()) {
    return false;
  }

  front = (front + 1) % capacity;
  size--;

  return true;
}

void Queue::print() {
  if (isEmpty()) {
    return;
  }

  for (int i = 0; i < size; i++) {
    int index = (front + i) % capacity;

    std::cout << arr[index] << " ";
  }
}

int main() {

  Queue queue(5);

  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);
  queue.enqueue(4);

  queue.print();
  std::cout << "\n";

  queue.dequeue();

  queue.print();

  return 0;
}
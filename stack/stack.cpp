#include <iostream>

// implementação de uma Stack (Pilha)

class Stack {
private:
  int top;
  int capacity;
  int *arr;

public:
  Stack(int capacity) {
    this->capacity = capacity;
    top = -1; // representa stack vazia
    arr = new int[capacity];
  }

  // destrutor
  ~Stack() { delete[] arr; }

  bool push(int value);
  int pop();
  int peek();
  void print();
};

// implementação

// método para adicionar elemento no topo da pilha
bool Stack::push(int value) {
  if (top >= capacity - 1) {
    return false; // stack overflow
  }

  arr[++top] = value; //
  return true;
}

// método para remover elemento do topo da pilha
int Stack::pop() {
  if (top < 0) {
    return -1; // stack underflow
  }

  return arr[top--];
}

// método para retornar o elemento do topo da pilha
int Stack::peek() {
  if (top < 0) {
    return -1; // stack vazia
  }

  return arr[top];
}

void Stack::print() {
  for (int i = top; i >= 0; i--) {
    std::cout << arr[i] << " ";
  }
}

int main() {

  Stack stack = Stack(5);

  stack.push(10);
  stack.push(20);
  stack.push(30);
  stack.push(40);
  stack.push(50);

  stack.print();
  return 0;
}
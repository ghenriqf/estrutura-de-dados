#include <iostream>

using namespace std;

struct Stack {
    int* data;
    int top;
    int capacity;
};

bool init(Stack* s, int initialCapacity = 4) {
    s->data = new(nothrow) int[initialCapacity];
    if (s->data == nullptr) return false;

    s->top = -1;
    s->capacity = initialCapacity;
    return true;
}

bool isEmpty(const Stack* s) {
    return s->top == -1;
}

bool resize(Stack* s) {
    int newCapacity = s->capacity * 2;
    int* newData = new(nothrow) int[newCapacity];

    if (newData == nullptr) return false;

    for (int i = 0; i <= s->top; i++) {
        newData[i] = s->data[i];
    }

    delete[] s->data;
    s->data = newData;
    s->capacity = newCapacity;

    return true;
}

bool push(Stack* s, int value) {
    if (s->top == s->capacity - 1) {
        if (!resize(s)) return false;
    }

    s->data[++(s->top)] = value;
    return true;
}

bool pop(Stack* s, int* out) {
    if (isEmpty(s)) return false;

    *out = s->data[(s->top)--];
    return true;
}

bool peek(const Stack* s, int* out) {
    if (isEmpty(s)) return false;

    *out = s->data[s->top];
    return true;
}

void print(const Stack* s) {
    if (isEmpty(s)) {
        cout << "Stack vazia\n";
        return;
    }

    cout << "Topo -> ";
    for (int i = s->top; i >= 0; i--) {
        cout << s->data[i] << " ";
    }
    cout << "\n";
}

void clear(Stack* s) {
    delete[] s->data;
    s->data = nullptr;
    s->top = -1;
    s->capacity = 0;
}

int main() {
    Stack s;

    if (!init(&s)) {
        cout << "Erro de memoria!\n";
        return 1;
    }

    for (int i = 1; i <= 10; i++) {
        push(&s, i * 10);
    }

    print(&s);

    int value;

    if (peek(&s, &value)) {
        cout << "Topo: " << value << "\n";
    }

    if (pop(&s, &value)) {
        cout << "Removido: " << value << "\n";
    }

    print(&s);

    clear(&s);
    return 0;
}
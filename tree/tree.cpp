#include <iostream>
using namespace std;

struct No {
  int valor;
  No *esquerda;
  No *direita;
};

No *criarNo(int valor) {
  No *novoNo = new No;
  novoNo->valor = valor;
  novoNo->esquerda = nullptr;
  novoNo->direita = nullptr;

  return novoNo;
}

bool isBST(No *arvore, int minimo, int maximo) {
  No *atual = arvore;

  if (atual == nullptr) {
    return true;
  }

  if (atual->valor < minimo || atual->valor > maximo) {
    return false;
  }

  return isBST(atual->esquerda, minimo, atual->valor - 1) &&
         isBST(atual->direita, maximo, atual->valor + 1);
}

No *inserir(No *arvore, int valor) {
  No *atual = arvore;

  if (arvore == nullptr) {
    return criarNo(valor);
  }

  if (valor < atual->valor) {
    atual->esquerda = inserir(atual->esquerda, valor);
  } else {
    atual->direita = inserir(atual->direita, valor);
  }

  return atual;
}

int contarFolhas(No *arvore) {
  No *atual = arvore;

  if (atual == nullptr) {
    return 0;
  }

  if (atual->esquerda == nullptr && atual->esquerda == nullptr) {
    return 1;
  }

  return contarFolhas(atual->esquerda) + contarFolhas(atual->direita);
}

void inOrder(No *arvore) {
  No *atual = arvore;
  if (atual != nullptr) {
    inOrder(atual->esquerda);
    cout << atual->valor << endl;
    inOrder(atual->direita);
  }
}

int main() {
  No *arvore = nullptr;
  arvore = inserir(arvore, 10);

  inserir(arvore, 30);
  inserir(arvore, 20);
  inserir(arvore, 50);
  inserir(arvore, 70);
  inserir(arvore, 60);
  inserir(arvore, 30);

  inOrder(arvore);

  cout << contarFolhas(arvore);
}
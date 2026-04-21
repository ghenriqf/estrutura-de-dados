#include <iostream>
using namespace std;

struct No {
  int dado;
  No *esq;
  No *dir;
};

int soma(No *no) {
  if (no == 0)
    return 0;
  return no->dado + soma(no->esq) + soma(no->dir);
}

int menorValor(No *no) {
  while (no->esq != 0)
    no = no->esq;
  return no->dado;
}

int maiorValor(No *no) {
  while (no->dir != 0)
    no = no->dir;
  return no->dado;
}

int contarUmFilho(No *no) {
  if (no == 0)
    return 0;

  int cont = 0;

  if ((no->esq == 0 && no->dir != 0) || (no->esq != 0 && no->dir == 0))
    cont = 1;

  return cont + contarUmFilho(no->esq) + contarUmFilho(no->dir);
}

void espelhar(No *no) {
  if (no == 0)
    return;

  No *temp = no->esq;
  no->esq = no->dir;
  no->dir = temp;

  espelhar(no->esq);
  espelhar(no->dir);
}

int altura(No *no) {
  if (no == 0)
    return 0;

  int esq = altura(no->esq);
  if (esq == -1)
    return -1;

  int dir = altura(no->dir);
  if (dir == -1)
    return -1;

  if ((esq - dir > 1) || (dir - esq > 1))
    return -1;

  return (esq > dir ? esq : dir) + 1;
}

bool estaBalanceada(No *raiz) { return altura(raiz) != -1; }
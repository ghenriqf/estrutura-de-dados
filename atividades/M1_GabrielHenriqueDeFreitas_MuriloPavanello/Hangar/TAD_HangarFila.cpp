#include "TAD_HangarFila.h"

HangarFila *inicializarFila()
{
  HangarFila *fila = new HangarFila;
  fila->frente = nullptr;
  fila->calda = nullptr;

  return fila;
}

void enqueue(int valor, HangarFila *fila)
{
  No *novoNo = new No;
  novoNo->valor = valor;
  novoNo->proximo = nullptr;

  if (fila->frente == nullptr && fila->calda == nullptr)
  {
    fila->frente = novoNo;
    fila->calda = novoNo;

    novoNo->proximo = nullptr;

    return;
  }

  fila->calda->proximo = novoNo;
  fila->calda = novoNo;

  novoNo->proximo = nullptr;
}

void dequeue(HangarFila *fila)
{
  No *temp = fila->frente;

  if (fila->frente == nullptr)
  {
    delete temp;
    return;
  }

  if (fila->frente == fila->calda)
  {
    delete temp;

    fila->frente = nullptr;
    fila->calda = nullptr;

    return;
  }

  fila->frente = fila->frente->proximo;

  delete temp;
}
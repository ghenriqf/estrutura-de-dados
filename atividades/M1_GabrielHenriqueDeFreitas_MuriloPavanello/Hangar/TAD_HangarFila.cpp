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
  NoHangar *novoNo = new NoHangar;
  novoNo->valor = valor;

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
  NoHangar *temp = fila->frente;

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
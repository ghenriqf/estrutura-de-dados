#include "TAD_CargaListaEncadeada.h"

CargaListaEncadeada *inicializarListaEncadeada()
{
  CargaListaEncadeada *lista = new CargaListaEncadeada;

  lista->cabeca = nullptr;

  return lista;
}

void inserirCarga(int valor, CargaListaEncadeada *lista)
{
  NoCarga *novoNo = new NoCarga;
  novoNo->carga = valor;
  novoNo->proximo = nullptr;

  if (lista->cabeca == nullptr)
  {
    lista->cabeca = novoNo;

    return;
  }

  novoNo->proximo = lista->cabeca;
  lista->cabeca = novoNo;
}

bool removerCarga(int valor, CargaListaEncadeada *lista)
{
  NoCarga *atual = lista->cabeca;

  if (lista->cabeca == nullptr)
  {
    return false;
  }

  if (lista->cabeca->carga == valor)
  {
    NoCarga *temporario = lista->cabeca;
    lista->cabeca = lista->cabeca->proximo;
    delete temporario;

    return true;
  }

  while (atual->proximo != nullptr && atual->proximo->carga != valor)
  {
    atual = atual->proximo;
  }

  if (atual->proximo != nullptr)
  {
    NoCarga *temporario = atual->proximo;
    atual->proximo = atual->proximo->proximo;

    delete temporario;

    return true;
  }

  return false;
}
#include "TAD_CargaListaDuplamenteEncadeada.h"
#include <iostream>

CargaListaDuplamenteEncadeada *inicializarListaEncadeada()
{
  CargaListaDuplamenteEncadeada *lista = new CargaListaDuplamenteEncadeada;

  lista->cabeca = nullptr;

  return lista;
}

void inserirCarga(int valor, CargaListaDuplamenteEncadeada *lista)
{
  No *novoNo = new No;
  novoNo->carga = valor;
  novoNo->proximo = nullptr;

  if (lista->cabeca == nullptr)
  {
    lista->cabeca = novoNo;

    return;
  }

  novoNo->proximo = lista->cabeca;
  lista->cabeca = novoNo;

  return;
}

bool removerCarga(int valor, CargaListaDuplamenteEncadeada *lista)
{
  No *atual = lista->cabeca;

  if (lista->cabeca == nullptr)
  {
    return false;
  }

  if (lista->cabeca->carga == valor)
  {
    No *temporario = lista->cabeca;
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
    No *temporario = atual->proximo;
    atual->proximo = atual->proximo->proximo;

    delete temporario;

    return true;
  }

  return false;
}
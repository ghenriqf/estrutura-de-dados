#include <iostream>

#include "TAD_NaveListaEncadeada.h"

NaveListaEncadeada *inicializarListaEncadeada()
{
  NaveListaEncadeada *lista = new NaveListaEncadeada;
  lista->cabeca = nullptr;
  lista->calda = nullptr;

  return lista;
}

void inserirNave(string nome, NaveListaEncadeada *lista)
{
  No *novoNo = new No;
  novoNo->nome = nome;
  novoNo->proximo = nullptr;
  novoNo->anterior = nullptr;

  if (lista->calda == nullptr)
  {
    lista->cabeca = novoNo;
    lista->calda = novoNo;
    return;
  }

  lista->calda->proximo = novoNo;
  novoNo->anterior = lista->calda;
  lista->calda = novoNo;
}

bool removerNave(string nome, NaveListaEncadeada *lista)
{
  No *atual = lista->cabeca;

  while (atual != nullptr)
  {
    if (atual->nome == nome)
    {
      if (atual == lista->cabeca && atual == lista->calda)
      {
        lista->cabeca = nullptr;
        lista->calda = nullptr;

        delete atual;
        return true;
      }
      else if (atual == lista->cabeca)
      {
        No *temporario = atual;

        lista->cabeca = lista->cabeca->proximo;
        lista->cabeca->anterior = nullptr;

        delete temporario;
        return true;
      }
      else if (atual == lista->calda)
      {
        No *temporario = atual;

        lista->calda = atual->anterior;
        lista->calda->proximo = nullptr;

        delete temporario;

        return true;
      }
      else
      {
        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;

        delete atual;

        return true;
      }
    }
    atual = atual->proximo;
  }

  return false;
}
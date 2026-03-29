#include "TAD_NaveListaDuplamenteEncadeada.h"

NaveListaDuplamenteEncadeada *inicializarListaDuplamenteEncadeada()
{
  NaveListaDuplamenteEncadeada *lista = new NaveListaDuplamenteEncadeada;
  lista->cabeca = nullptr;
  lista->calda = nullptr;

  return lista;
}

void inserirNave(string nome, NaveListaDuplamenteEncadeada *lista)
{
  NoNave *novoNo = new NoNave;
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

bool removerNave(string nome, NaveListaDuplamenteEncadeada *lista)
{
  if (lista->cabeca == nullptr)
    return false;

  NoNave *atual = lista->cabeca;

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
        NoNave *temporario = atual;

        lista->cabeca = lista->cabeca->proximo;
        lista->cabeca->anterior = nullptr;

        delete temporario;
        return true;
      }
      else if (atual == lista->calda)
      {
        NoNave *temporario = atual;

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
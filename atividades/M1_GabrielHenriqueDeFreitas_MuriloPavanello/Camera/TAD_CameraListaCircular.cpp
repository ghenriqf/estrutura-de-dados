#include "TAD_CameraListaCircular.h"

CameraListaCircular *inicializarListaCircular()
{
  CameraListaCircular *lista = new CameraListaCircular;
  lista->cabeca = nullptr;

  return lista;
}

void inserirCamera(int valor, CameraListaCircular *lista)
{
  NoCamera *novoNo = new NoCamera;
  novoNo->camera = valor;

  if (lista->cabeca == nullptr)
  {
    lista->cabeca = novoNo;
    novoNo->proximo = lista->cabeca;
    return;
  }

  NoCamera *temporario = lista->cabeca;

  while (temporario->proximo != lista->cabeca)
  {
    temporario = temporario->proximo;
  }

  temporario->proximo = novoNo;
  novoNo->proximo = lista->cabeca;
}

bool removerCamera(int valor, CameraListaCircular *lista)
{
  if (lista->cabeca == nullptr)
    return false;

  NoCamera *atual = lista->cabeca;

  if (lista->cabeca->camera == valor)
  {
    if (atual->proximo == lista->cabeca)
    {
      delete lista->cabeca;
      lista->cabeca = nullptr;
      return true;
    }

    NoCamera *ultimo = lista->cabeca;

    while (ultimo->proximo != lista->cabeca)
    {
      ultimo = ultimo->proximo;
    }

    lista->cabeca = lista->cabeca->proximo;
    ultimo->proximo = lista->cabeca;

    delete atual;
    return true;
  }

  NoCamera *anterior = lista->cabeca;
  atual = lista->cabeca->proximo;

  while (atual != lista->cabeca)
  {
    if (atual->camera == valor)
    {
      anterior->proximo = atual->proximo;
      delete atual;
      return true;
    }

    anterior = atual;
    atual = atual->proximo;
  }

  return false;
}
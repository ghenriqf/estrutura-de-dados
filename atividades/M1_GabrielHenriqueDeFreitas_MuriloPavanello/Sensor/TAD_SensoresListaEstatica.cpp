#include "TAD_SensoresListaEstatica.h"

SensoresListaEstatica *inicializarListaEstatica()
{
  SensoresListaEstatica *lista = new SensoresListaEstatica;

  lista->sensores = new int[CAPACIDADE];
  lista->quantidadeElementos = 0;

  return lista;
}

bool inserirSensor(int valor, SensoresListaEstatica *lista)
{
  if (lista->quantidadeElementos >= CAPACIDADE)
  {
    return false;
  }

  lista->sensores[lista->quantidadeElementos] = valor;
  lista->quantidadeElementos++;

  return true;
}

bool removerSensor(int valor, SensoresListaEstatica *lista)
{
  for (int i = 0; i < lista->quantidadeElementos; i++)
  {
    if (lista->sensores[i] == valor)
    {
      for (int j = i; j < lista->quantidadeElementos - 1; j++)
      {
        lista->sensores[j] = lista->sensores[j + 1];
      }

      lista->quantidadeElementos--;
      return true;
    }
  }

  return false;
}
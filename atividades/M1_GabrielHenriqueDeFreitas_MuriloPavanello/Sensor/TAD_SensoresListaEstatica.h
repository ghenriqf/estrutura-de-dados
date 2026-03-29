#ifndef TAD_SENSORES_LISTA_ESTATICA_H
#define TAD_SENSORES_LISTA_ESTATICA_H

#define CAPACIDADE 5

struct SensoresListaEstatica
{
  int *sensores;
  int quantidadeElementos;
};

bool inserirSensor(int valor, SensoresListaEstatica *lista);
bool removerSensor(int valor, SensoresListaEstatica *lista);
SensoresListaEstatica *inicializarListaEstatica();

#endif
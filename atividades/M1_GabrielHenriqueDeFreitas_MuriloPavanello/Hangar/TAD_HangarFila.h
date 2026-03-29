#ifndef TAD_HANGAR_FILA_H
#define TAD_HANGAR_FILA_H

struct No
{
  int valor;
  No *proximo;
};

struct HangarFila
{
  No *frente;
  No *calda;
};

void enqueue(int valor, HangarFila *fila);
void dequeue(HangarFila *fila);
HangarFila *inicializarFila();

#endif
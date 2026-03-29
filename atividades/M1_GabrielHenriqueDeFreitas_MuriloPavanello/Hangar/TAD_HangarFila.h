#ifndef TAD_HANGAR_FILA_H
#define TAD_HANGAR_FILA_H

struct NoHangar
{
  int valor;
  NoHangar *proximo;
};

struct HangarFila
{
  NoHangar *frente;
  NoHangar *calda;
};

void enqueue(int valor, HangarFila *fila);
void dequeue(HangarFila *fila);
HangarFila *inicializarFila();

#endif
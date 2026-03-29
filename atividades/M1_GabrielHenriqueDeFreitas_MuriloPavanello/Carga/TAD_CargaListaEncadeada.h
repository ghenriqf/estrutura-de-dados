#ifndef TAD_CARGA_LISTA_ENCADEADA_H
#define TAD_CARGA_LISTA_ENCADEADA_H

struct NoCarga
{
  int carga;
  NoCarga *proximo;
};

struct CargaListaEncadeada
{
  NoCarga *cabeca;
};

void inserirCarga(int valor, CargaListaEncadeada *lista);
bool removerCarga(int valor, CargaListaEncadeada *lista);
CargaListaEncadeada *inicializarListaEncadeada();

#endif
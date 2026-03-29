#ifndef TAD_CARGA_LISTA_ENCADEADA_H
#define TAD_CARGA_LISTA_ENCADEADA_H

struct No
{
  int carga;
  No *proximo;
};

struct CargaListaEncadeada
{
  No *cabeca;
};

void inserirCarga(int valor, CargaListaEncadeada *lista);
bool removerCarga(int valor, CargaListaEncadeada *lista);
CargaListaEncadeada *inicializarListaEncadeada();

#endif
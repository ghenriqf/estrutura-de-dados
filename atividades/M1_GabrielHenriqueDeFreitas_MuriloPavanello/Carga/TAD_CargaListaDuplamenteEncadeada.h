#ifndef TAD_CARGA_LISTA_DUPLAMENTE_ENCADEADA_H
#define TAD_CARGA_LISTA_DUPLAMENTE_ENCADEADA_H

struct No
{
  int carga;
  No *proximo;
};

struct CargaListaDuplamenteEncadeada
{
  No *cabeca;
};

void inserirCarga(int valor, CargaListaDuplamenteEncadeada *lista);
bool removerCarga(int valor, CargaListaDuplamenteEncadeada *lista);
CargaListaDuplamenteEncadeada *inicializarListaEncadeada();

#endif
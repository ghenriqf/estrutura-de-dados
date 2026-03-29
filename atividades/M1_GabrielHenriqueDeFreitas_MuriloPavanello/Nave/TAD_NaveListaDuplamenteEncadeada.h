#ifndef TAD_NAVE_LISTA_DUPLAMENTE_ENCADEADA
#define TAD_NAVE_LISTA_DUPLAMENTE_ENCADEADA
#include <iostream>
using namespace std;

struct NoNave
{
  string nome;
  NoNave *proximo;
  NoNave *anterior;
};

struct NaveListaDuplamenteEncadeada
{
  NoNave *cabeca;
  NoNave *calda;
};

void inserirNave(string nome, NaveListaDuplamenteEncadeada *lista);
bool removerNave(string nome, NaveListaDuplamenteEncadeada *lista);
NaveListaDuplamenteEncadeada *inicializarListaDuplamenteEncadeada();

#endif
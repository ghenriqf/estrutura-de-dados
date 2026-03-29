#ifndef TAD_NAVE_LISTA_DUPLAMENTE_ENCADEADA
#define TAD_NAVE_LISTA_DUPLAMENTE_ENCADEADA
#include <iostream>
using namespace std;

struct No
{
  string nome;
  No *proximo;
  No *anterior;
};

struct NaveListaDuplamenteEncadeada
{
  No *cabeca;
  No *calda;
};

void inserirNave(string nome, NaveListaDuplamenteEncadeada *lista);
bool removerNave(string nome, NaveListaDuplamenteEncadeada *lista);
NaveListaDuplamenteEncadeada *inicializarListaEncadeada();

#endif
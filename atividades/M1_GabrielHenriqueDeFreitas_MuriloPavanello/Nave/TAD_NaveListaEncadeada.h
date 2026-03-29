#ifndef TAD_NAVE_LISTA_ENCADEADA
#define TAD_NAVE_LISTA_ENCADEADA
#include <iostream>
using namespace std;

struct No
{
  string nome;
  No *proximo;
  No *anterior;
};

struct NaveListaEncadeada
{
  No *cabeca;
  No *calda;
};

void inserirNave(string nome, NaveListaEncadeada *lista);
bool removerNave(string nome, NaveListaEncadeada *lista);
NaveListaEncadeada *inicializarListaEncadeada();

#endif
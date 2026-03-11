#include <iostream>

using namespace std;

struct ListaSimples
{
    No *inicio;
};

struct No
{
    int valor;
    No *proximo;
};

ListaSimples *criarListaSimples()
{
    ListaSimples *lista = (ListaSimples *)calloc(1, sizeof(ListaSimples));

    No *proximo;

    lista->inicio = proximo;
}

int main()
{
    return 0;
}
#include <iostream>
using namespace std;

struct ListaDinamica
{
    int *arr;
    int capacidade;
    int quantidade;
};

void inicializar(ListaDinamica *l)
{
    l->capacidade = 10;
    l->quantidade = 0;
    l->arr = (int *)malloc(l->capacidade * sizeof(int));
}

bool inserir(ListaDinamica *l, int valor)
{
    if (l->quantidade == l->capacidade)
    {
        int novaCapacidade = l->capacidade * 2;
        int *novoArray = (int *)malloc(novaCapacidade * sizeof(int));

        for (int i = 0; i < l->quantidade; i++)
        {
            novoArray[i] = l->arr[i];
        }

        free(l->arr);
        l->arr = novoArray;
        l->capacidade = novaCapacidade;
    }

    l->arr[l->quantidade] = valor;
    l->quantidade++;
    return true;
}

void atualizar(ListaDinamica *l, int indice, int novoValor)
{
    if (indice < 0 || indice >= l->quantidade)
    {
        cout << "Indice invalido!" << endl;
        return;
    }

    l->arr[indice] = novoValor;
}

int buscar(ListaDinamica *l, int valor)
{
    for (int i = 0; i < l->quantidade; i++)
    {
        if (l->arr[i] == valor)
        {
            return i;
        }
    }
    return -1;
}

bool remover(ListaDinamica *l, int valor)
{
    int indice = buscar(l, valor);

    if (indice == -1)
        return false;

    for (int i = indice; i < l->quantidade - 1; i++)
    {
        l->arr[i] = l->arr[i + 1];
    }

    l->quantidade--;
    return true;
}

void liberar(ListaDinamica *l)
{
    free(l->arr);
}
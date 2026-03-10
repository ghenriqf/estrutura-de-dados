#include <iostream>

using namespace std;

struct ListaEstatica
{
    int arr[10];
    int quantidade;
};

void inicializar(ListaEstatica *l)
{
    l->quantidade = 0;
}

bool inserir(ListaEstatica *l, int valor)
{
    if (l->quantidade == 10)
    {
        return false;
    }
    l->arr[9 - l->quantidade] = valor;
    l->quantidade++;

    return true;
}

int buscar(ListaEstatica *l, int valor)
{
    for (int i = 0; i <= 10; i++)
    {
        if (l->arr[i] == valor)
        {
            return i;
        }
    }

    return -1;
}

bool remover(ListaEstatica *l, int valor)
{
    int indice = buscar(l, valor);

    if (indice == -1)
    {
        return false;
    }

    for (int i = indice; i < l->quantidade - 1; i++)
    {
        l->arr[i] = l->arr[i + 1];
    }

    l->quantidade--;
    return true;
}

int main()
{
    return 0;
}
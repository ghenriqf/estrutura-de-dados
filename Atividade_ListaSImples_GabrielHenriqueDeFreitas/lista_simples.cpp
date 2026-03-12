#include <iostream>

using namespace std;

struct No
{
    int valor;
    No *proximo;
};

struct ListaSimples
{
    No *inicio;
};

ListaSimples *criar_lista_simples()
{
    ListaSimples *lista = (ListaSimples *)calloc(1, sizeof(ListaSimples));
    lista->inicio = nullptr;

    return lista;
}

void inserir_ordenado(ListaSimples *lista, int valor)
{
    No *no = (No *)calloc(1, sizeof(No));
    no->valor = valor;
    no->proximo = nullptr;

    if (lista->inicio == nullptr || lista->inicio->valor > valor)
    {
        no->proximo = lista->inicio;
        lista->inicio = no;
        return;
    }
    else
    {
        No *atual = lista->inicio;
        No *proximo = lista->inicio->proximo;

        while (proximo != nullptr)
        {
            if (atual->valor < valor && proximo->valor > valor)
            {
                no->proximo = proximo;
                atual->proximo = no;
                break;
            }
            atual = proximo;
            proximo = proximo->proximo;
        }

        atual->proximo = no;
    }
}

void imprimir_lista_simples(ListaSimples *lista)
{
    No *no = lista->inicio;

    while (no != NULL)
    {
        cout << no->valor << " -> ";
        no = no->proximo;
    }
}

No *buscar_no(ListaSimples *lista, int valor)
{
    No *no = lista->inicio;

    while (no->valor != valor)
    {
        no = no->proximo;
    }

    return no;
}

int contar_nos(ListaSimples *lista)
{
    No *no = lista->inicio;
    int quantidade_nos = 0;

    while (no != NULL)
    {
        quantidade_nos++;
        no = no->proximo;
    }

    return quantidade_nos;
}

int main()
{

    ListaSimples *lista = criar_lista_simples();
    inserir_ordenado(lista, 10);
    inserir_ordenado(lista, 4);
    inserir_ordenado(lista, 20);
    inserir_ordenado(lista, 1);
    inserir_ordenado(lista, 50);

    imprimir_lista_simples(lista);

    return 0;
}
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

    No *atual = lista->inicio;

    while (atual->proximo != nullptr && atual->proximo->valor < valor)
    {
        atual = atual->proximo;
    }

    no->proximo = atual->proximo;
    atual->proximo = no;
}

void inverter_lista(ListaSimples *lista)
{
    No *atual = lista->inicio;
    No *novo_inicio = nullptr;
    No *proximo = nullptr;

    while (atual != nullptr)
    {
        proximo = atual->proximo;
        atual->proximo = novo_inicio;
        novo_inicio = atual;
        atual = proximo;
    }

    lista->inicio = novo_inicio;
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

    while (no != nullptr)
    {
        quantidade_nos++;
        no = no->proximo;
    }

    return quantidade_nos;
}

void liberar_lista(ListaSimples *lista)
{
    No *atual = lista->inicio;
    No *proximo;

    while (atual != nullptr)
    {
        proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
    lista->inicio = nullptr;
}

int main()
{

    ListaSimples *lista = criar_lista_simples();

    inserir_ordenado(lista, 50);
    inserir_ordenado(lista, 10);
    inserir_ordenado(lista, 30);

    imprimir_lista_simples(lista);
    cout << endl;
    cout << contar_nos(lista) << endl;

    inverter_lista(lista);
    imprimir_lista_simples(lista);

    cout << endl
         << buscar_no(lista, 10);

    liberar_lista(lista);

    return 0;
}
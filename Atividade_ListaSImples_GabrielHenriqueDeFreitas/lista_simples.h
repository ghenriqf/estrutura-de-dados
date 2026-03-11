#ifndef LISTA_SIMPLES
#define LISTA_SIMPLES

typedef struct No
{
    int valor;
    No *proximo;
};

typedef struct ListaSimples
{
    No *inicio;
};

ListaSimples *criarListaSimples();

void imprimirListaSimples(ListaSimples *lista);

void inserirOrdenado(ListaSimples *lista, int valor);

int contarNos(ListaSimples *lista);

No *buscarNo(ListaSimples *lista, int valor);

void inverterLista(ListaSimples *lista);

void liberarLista(ListaSimples *lista);

#endif
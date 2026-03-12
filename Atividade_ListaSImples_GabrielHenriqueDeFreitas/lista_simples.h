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

void imprimir_lista_simples(ListaSimples *lista);

void inserir_ordenado(ListaSimples *lista, int valor);

int contar_nos(ListaSimples *lista);

No *buscar_no(ListaSimples *lista, int valor);

void inverter_lista(ListaSimples *lista);

void liberar_lista(ListaSimples *lista);

#endif
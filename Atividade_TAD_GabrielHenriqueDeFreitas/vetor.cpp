#include <iostream>
#include <cstdlib>
#include "vetor.h"

using namespace std;

struct vetor {
    int capacidade;
    int elementos;
    float* dados;
};

Vetor* vet_cria(int cap) {
    vetor *v = (vetor*) malloc(sizeof(vetor));

    v->capacidade = cap;
    v->elementos = 0;
    v->dados = (float*) malloc(cap * sizeof(float));

    return v;
}

void vet_insere (Vetor *v, float valor) {
    if (v->elementos >= v->capacidade) {
        int novaCapacidade = v->capacidade * 2;
        float *novoDados = (float*) malloc(novaCapacidade * sizeof(float));

        for (int i = 0; i < v->elementos; i++) {
            novoDados[i] = v->dados[i];
        }

        free(v->dados);
        v->dados = novoDados;
        v->capacidade = novaCapacidade;
    }

    v->dados[v->elementos] = valor;
    v->elementos++;
}

float vet_acessa (Vetor *v, int i) {
    if (i < 0 || i >= v->elementos) return -1; // -1 = erro

    return v->dados[i];
}

int vet_tamanho(Vetor* v) {
    return v->elementos;
}

void vet_libera(Vetor* v) {
    free(v->dados);
    free(v);
}
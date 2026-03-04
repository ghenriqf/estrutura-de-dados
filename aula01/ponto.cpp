#include <iostream>
#include <math.h>
#include "ponto.h"

using namespace std;

struct ponto {
    float x;
    float y;
};

Ponto* criar (float x, float y) {
    Ponto* ponto = (Ponto*) malloc(sizeof(Ponto));

    ponto->x = x;
    ponto->y = y;

    return ponto;
}

float calcularDistancia (Ponto *ponto1, Ponto *ponto2) {
    float dx = ponto1->x - ponto2->x;
    float dy = ponto1->y - ponto2->y;

    float distancia = sqrt(dx * dy + dy * dy);

    return distancia;
}
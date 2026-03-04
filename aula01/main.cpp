#include <iostream>
#include "ponto.h"

using namespace std;

int main () {
    Ponto *ponto1 = criar(1.0, 1.2);
    Ponto *ponto2 = criar(1.0, 1.0);

    float distancia = calcularDistancia(ponto1, ponto2);

    cout << distancia;

    return 0;
}
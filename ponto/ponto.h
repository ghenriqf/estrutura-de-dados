#ifndef PONTO_H
#define PONTO_H

typedef struct ponto Ponto;

Ponto *criar (float x, float y);
void destruir (Ponto ponto);

void definir (Ponto *ponto, float x, float y);
void obter (Ponto &ponto, float x, float y);

float calcularDistancia (Ponto *ponto1, Ponto *ponto2);

#endif
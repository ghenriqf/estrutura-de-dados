#ifndef TAD_LOG_PILHA_H
#define TAD_LOG_PILHA_H
#include <iostream>
using namespace std;

struct NoPilha
{
  string log;
  NoPilha *proximo;
};

struct LogPilha
{
  NoPilha *topo;
};

void push(string log, LogPilha *pilha);
string pop(LogPilha *pilha);
LogPilha *inicializarPilha();

#endif
#include <iostream>
#include "TAD_LogPilha.h"

LogPilha *inicializarPilha()
{
  LogPilha *pilha = new LogPilha;
  pilha->topo = nullptr;

  return pilha;
}

void push(string log, LogPilha *pilha)
{
  No *novoNo = new No;
  novoNo->log = log;
  novoNo->proximo = pilha->topo;

  pilha->topo = novoNo;
}

string pop(LogPilha *pilha)
{
  if (pilha->topo == nullptr)
    return "";

  No *no = pilha->topo;
  string log = no->log;

  pilha->topo = pilha->topo->proximo;
  delete no;

  return log;
}
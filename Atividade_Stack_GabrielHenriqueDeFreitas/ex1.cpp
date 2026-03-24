#include <iostream>
using namespace std;

#define MAX 100

struct PilhaEstatica {
    char dados[MAX];
    int topo;
};

void inicializar(PilhaEstatica &p) {
    p.topo = -1;
}

bool estaCheia(PilhaEstatica &p) {
    return p.topo == MAX - 1;
}

bool estaVazia(PilhaEstatica &p) {
    return p.topo == -1;
}

bool empilhar(PilhaEstatica &p, char c) {
    if (estaCheia(p)) {
        cout << "Erro: pilha cheia!" << endl;
        return false;
    }
    p.dados[++p.topo] = c;
    return true;
}

char desempilhar(PilhaEstatica &p) {
    if (estaVazia(p)) {
        cout << "Erro: pilha vazia!" << endl;
        return '\0';
    }
    return p.dados[p.topo--];
}

int main() {
    PilhaEstatica pilha;
    inicializar(pilha);

    string palavra;
    cout << "Digite uma palavra: ";
    cin >> palavra;

    cout << "\nEmpilhando caracteres..." << endl;
    for (int i = 0; i < palavra.size(); i++) {
        empilhar(pilha, palavra[i]);
        cout << "  Empilhou: '" << palavra[i] << "'" << endl;
    }

    cout << "\nDesempilhando e imprimindo..." << endl;
    cout << "Resultado: ";
    while (!estaVazia(pilha)) {
        cout << desempilhar(pilha);
    }
    cout << endl;

    return 0;
}
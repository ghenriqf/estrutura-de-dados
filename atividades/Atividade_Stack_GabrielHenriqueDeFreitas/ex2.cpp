#include <iostream>
#include <string>
using namespace std;

struct No {
    char dado;
    No* proximo;
};

struct PilhaDinamica {
    No* topo;
    int tamanho;
};

void inicializar(PilhaDinamica &p) {
    p.topo = nullptr;
    p.tamanho = 0;
}

bool estaVazia(PilhaDinamica &p) {
    return p.topo == nullptr;
}

void empilhar(PilhaDinamica &p, char c) {
    No* novo = new No();
    novo->dado = c;
    novo->proximo = p.topo;
    p.topo = novo;
    p.tamanho++;
}

char desempilhar(PilhaDinamica &p) {
    if (estaVazia(p)) {
        cout << "Erro: pilha vazia!" << endl;
        return '\0';
    }
    No* temp = p.topo;
    char dado = temp->dado;
    p.topo = p.topo->proximo;
    delete temp;
    p.tamanho--;
    return dado;
}

char topo(PilhaDinamica &p) {
    if (estaVazia(p)) return '\0';
    return p.topo->dado;
}

void liberar(PilhaDinamica &p) {
    while (!estaVazia(p)) desempilhar(p);
}

bool validarParenteses(const string &expr) {
    PilhaDinamica pilha;
    inicializar(pilha);

    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == '(') {
            empilhar(pilha, c);
        } else if (c == ')') {
            if (estaVazia(pilha)) {
                liberar(pilha);
                return false;
            }
            desempilhar(pilha);
        }
    }

    bool balanceado = estaVazia(pilha);
    liberar(pilha);
    return balanceado;
}

int main() {
    string expressao;
    cout << "Digite uma expressao: ";
    cin >> expressao;

    cout << "\nAnalisando: " << expressao << endl;
    PilhaDinamica pilha;
    inicializar(pilha);
    bool erro = false;

    for (int i = 0; i < expressao.size(); i++) {
        char c = expressao[i];
        if (c == '(') {
            empilhar(pilha, c);
            cout << "  Pos " << i << ": '" << c << "' -> Empilhou  (abertos: " << pilha.tamanho << ")" << endl;
        } else if (c == ')') {
            if (estaVazia(pilha)) {
                cout << "  Pos " << i << ": '" << c << "' -> ERRO! Fechou sem abrir!" << endl;
                erro = true;
                break;
            }
            desempilhar(pilha);
            cout << "  Pos " << i << ": '" << c << "' -> Desempilhou (abertos: " << pilha.tamanho << ")" << endl;
        }
    }

    if (erro || !estaVazia(pilha)) {
        cout << "Resultado: PARENTESES DESBALANCEADOS!" << endl;
        if (!erro)
            cout << "Motivo: " << pilha.tamanho << " parentese(s) aberto(s) sem fechar." << endl;
    } else {
        cout << "Resultado: PARENTESES BALANCEADOS!" << endl;
    }

    liberar(pilha);
    return 0;
}
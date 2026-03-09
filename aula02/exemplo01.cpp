#include <iostream>

using namespace std;

int main () {
    int vetor[] = {4,7,19,2,1};

    int *p = vetor; 
    int n = 3;

    cout << "Valor de p (endereco inicial): " << p << endl;
    cout << "Valor de n: " << n << endl;

    int *resultado = p + n;

    cout << "Equacao do slide: p + n = 100 + (n*4)" << endl;
    cout << "Endereco final (p + 3): " << resultado << endl;
    cout <<"Valor do endereco (vetor[3]):   " << *resultado << endl;

    return 0;
}
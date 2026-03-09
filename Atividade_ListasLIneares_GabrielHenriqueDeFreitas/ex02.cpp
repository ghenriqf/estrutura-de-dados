#include <iostream>

using namespace std;

void inverter (int *vet, int tamanho) {
    int *inicio = vet;
    int *fim = vet + (tamanho - 1);

    for (int i = 0; i <= tamanho; i++) {
        int temp;

        temp = *inicio;
        *inicio = *fim;
        *fim = temp;

        inicio++;
        fim--;
    }
}

int main () {
    int vet[5] = {1,2,3,4,5};

    inverter(vet, 5);

    for (int v: vet) {
        cout << v << endl;
    }

}
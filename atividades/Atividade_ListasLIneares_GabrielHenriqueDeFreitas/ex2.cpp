#include <iostream>

using namespace std;

void inverter(int *vet, int tamanho)
{
    int *inicio = vet;
    int *fim = vet + (tamanho - 1);

    for (int i = 0; i < tamanho / 2; i++)
    {
        int temp;

        temp = *(inicio);
        *(inicio) = *(fim);
        *(fim) = temp;

        inicio = (inicio + 1);
        fim = (fim - 1);
    }
}

int main()
{
    int vet[5] = {1, 2, 3, 4, 5};

    inverter(vet, 5);

    for (int i : vet)
    {
        cout << i << " ";
    }

    return 0;
}
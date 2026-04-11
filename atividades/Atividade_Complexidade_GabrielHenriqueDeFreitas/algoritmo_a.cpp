#include <iostream>
#include <time.h>

using namespace std;

bool temDuplicado(int arr[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    for (int j = i + 1; j < tamanho; j++) {
      if (arr[i] == arr[j]) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int N = 50000;
  int arr[N];

  for (int i = 0; i < N; i++) {
    arr[i] = rand();
  }

  clock_t inicio, fim;
  double tempo_cpu;

  inicio = clock();

  temDuplicado(arr, N);

  fim = clock();

  tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  cout << tempo_cpu << endl;
}

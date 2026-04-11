#include <iostream>
#include <time.h>
using namespace std;

#define MAX 1000000

bool temDuplicado(int arr[], int tamanho) {
  int *hash = (int *)calloc(MAX, sizeof(int));

  for (int i = 0; i < tamanho; i++) {
    if (hash[arr[i]] == 1) {
      free(hash);
      return true;
    }
    hash[arr[i]] = 1;
  }

  free(hash);
  return false;
}

int main() {
  int N = 50000;
  int arr[N];

  for (int i = 0; i < N; i++) {
    arr[i] = rand() % MAX;
  }

  clock_t inicio, fim;
  double tempo_cpu;

  inicio = clock();

  temDuplicado(arr, N);

  fim = clock();

  tempo_cpu = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  cout << tempo_cpu << endl;
}

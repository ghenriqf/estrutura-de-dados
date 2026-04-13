#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

bool temDuplicado(int arr[], int tamanho) {
  qsort(arr, tamanho, sizeof(int), comp);

  for (int i = 1; i < tamanho; i++) {
    if (arr[i] == arr[i - 1]) {
      return true;
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
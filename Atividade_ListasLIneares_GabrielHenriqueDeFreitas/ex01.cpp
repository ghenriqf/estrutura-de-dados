#include <iostream>

using namespace std;

int main () {
    int *vetor = (int*) malloc(5 * sizeof(int));

    for (int i = 0; i <= 5; i++) {
        int n;
        cout << "Digite um valor para a posicao " << i << " : ";
        cin >> n;

        *(vetor + i) = n;

        cout << n << endl;
        cout << vetor + i << endl;
    }
    
    return 0;
}
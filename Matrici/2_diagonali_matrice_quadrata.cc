#include <iostream>
using namespace std;

int main() {
    const int N = 5;

    int mat[N][N];

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++) {
            cout << "Inserisci l'elemento " << i << " " << j << ": ";
            cin >> mat[i][j];
        }

    int primaria = 0, secondaria = 0;
    for(int i=0; i<N; i++) {
        primaria += mat[i][i];                  //calcolo diagonale principale
        secondaria += mat[i][N-i-1];            //calcolo diagonale secondaria
    }

    cout << "Differenza: " << primaria - secondaria << endl;

}

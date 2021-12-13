#include <iostream>
using namespace std;

int main() {
    const int RIGHE = 3, COLONNE = 2;
    //attenzione che se uso x, y allora x = COLONNE e y = RIGHE

    int mat[RIGHE][COLONNE];

    //metodo 1 per scorrere la matrice
    for(int i=0; i<RIGHE; i++)  //primo indice
        for(int j=0; j<COLONNE; j++) {
            cout << "Inserisci l'elemento " << i << " " << j << ": ";
            cin >> mat[i][j];
        }

    //stampare una matrice
    for(int i=0; i<RIGHE; i++) {
        for(int j=0; j<COLONNE; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

}
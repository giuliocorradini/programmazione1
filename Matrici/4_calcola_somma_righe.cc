#include <iostream>
using namespace std;

const int RIGHE = 3, COLONNE = 4;

int calcola_somma(const int m[], const int col) {
    int somma = 0;

    for(int i=0; i<col; i++)
        somma += m[i];

    return somma;
}

int main() {
    int mat[RIGHE][COLONNE];

    for(int i=0; i<RIGHE; i++)
        for(int j=0; j<COLONNE; j++) {
            cout << "Inserisci l'elemento " << i << " " << j << ": ";
            cin >> mat[i][j];
        }


    //Per "estrarre" una riga dalla matrice posso specificare solo l'indice della riga,
    //e mi verrà restituito un puntatore al primo elemento. Comodo no?
    for(int i=0; i<RIGHE; i++)
        cout << "Somma riga " << i << " = " << calcola_somma(mat[i], COLONNE) << endl;

}

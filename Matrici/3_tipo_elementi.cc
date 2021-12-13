/*
 *  Scrivere un programma che stampi il numero di elementi positivi, negativi e neutri
 *  contenuti nella matrice;
 */

#include <iostream>
#include <ctime>
using namespace std;

int main() {
    const int dim_x = 100, dim_y = 50;
    int mat[dim_y][dim_x];

    int positivi = 0, negativi = 0;

    srand(time(NULL));

    for(int i=0; i<dim_y; i++)
        for(int j=0; j<dim_x; j++)
            mat[i][j] = rand();

    for(int i=0; i<dim_y; i++)
        for(int j=0; j<dim_y; j++) {
            if(mat[i][j] > 0)
                positivi++;
            else if(mat[i][j] < 0)
                negativi++;
        }

    cout << "La matrice ha " << positivi << " valori positivi, " << negativi << " valori negativi e " << (dim_x * dim_y) - positivi - negativi << " valori neutri." << endl;

}

#include <iostream>
using namespace std;

void crea_copia_array(const int src[], const int dim, int *&dst) {
    dst = new int[dim];
    for(int i=0; i<dim; i++)
        dst[i] = src[i];
}
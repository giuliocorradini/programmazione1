/*
Scrivere un programma che crei dinamicamente un array di int, di
dimensioni inserite dall'utente da tastiera, e che lo riempia con
valori anch'essi inseriti dall'utente. Quindi il programma stampa il
contenuto dell'array.

A questo punto, il programma conserva in memoria SOLO una parte degli
elementi iniziali dell'array. In particolare chiede all'utente di
inserire un numero naturale n non maggiore delle dimensioni dell'array
e conserva in memoria solo i primi n elementi dell'array.  Quindi
stampa il sotto-array conservato in memoria, lo dealloca e termina.

Esempio:

Dimensioni array? 4
Valore elemento 1/4? 3
Valore elemento 2/4? 2
Valore elemento 3/4? 1
Valore elemento 4/4? 2

Valore elemento 1/4: 3
Valore elemento 2/4: 2
Valore elemento 3/4: 1
Valore elemento 4/4: 2
Numero di elementi da preservare? 2

Sotto-array:
Valore elemento 1/2: 3
Valore elemento 2/2: 2

*/

#include <iostream>
#include <cstring>
using namespace std;

int main() {

    int N;
    cout << "Inserisci le dimensioni dell'array: ";
    cin >> N;

    //1. crea
    int *a = new int[N];

    //2. riempi
    for(int i=0; i<N; i++) {
        cout << "Inserisci l'elemento " << i+1 << ": ";
        cin >> a[i];
    }

    //3. stampa
    cout << "<";
    for(int i=0; i<N; i++) {
        if(i != 0)
            cout << ", ";
        cout << a[i];
    }
    cout << ">" << endl;

    //4. Preserva
    int new_n;
    cout << "Numero di elementi da preservare? ";
    cin >> new_n;

    int *new_p = new int[new_n];
    memcpy(new_p, a, sizeof(int) * new_n);

    cout << "<";
    for(int i=0; i<new_n; i++) {
        if(i != 0)
            cout << ", ";
        cout << new_p[i];
    }
    cout << ">" << endl;

    //5. Distruggi
    delete [] a;

    delete [] new_p;

    return 0;
}
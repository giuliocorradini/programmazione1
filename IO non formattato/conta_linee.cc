/*
  Scrivere un programma che, senza effettuare letture formattate:

  1) crei un file di testo di nome Testo.txt;

  2) chieda all'utente di inserire il contenuto del file, carattere
  per carattere (gestire opportunamente la comunicazione della fine
  dell'immissione dei caratteri da parte dell'utente e ricordarsi che
  si possono effettuare solo letture non formattate);

  3) chiuda il file;

  4) lo riapra in lettura;

  5) ne stampi il contenuto ed il numero di righe.

  */

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    const char NOME_FILE[] = "Testo.txt";


    ofstream f(NOME_FILE);    //se il file non esiste viene creato
                                //se già presente viene distrutto e ricreato

    cout << "Inserisci il contenuto del file "<<NOME_FILE<<", termina con EOF" << endl;
    char c;
    while(cin.get(c)) {
        f << c;
    }

    f.close();


    ifstream f2(NOME_FILE);
    cout << "Contenuto del file:" << endl;

    int righe = 0;
    while(f2.get(c)) {
        if(c == '\n')
            righe++;
        cout << c;
    }

    cout << "per un totale di " << righe << " righe" << endl;

    return 0;
}
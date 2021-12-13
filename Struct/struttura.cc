#include <iostream>
#include <cstring>

using namespace std;

struct partecipante {
    char nome[32];
    int tempo;
};

int main() {

    struct partecipante p;

    cout << "Inserisci i dati del partecipante" << endl;

    cout << "Nome: ";
    cin >> p.nome;

    int tempo;
    cout <<  "Tempo di " << p.nome << " [min e sec]: ";
    cin >> tempo;
    p.tempo = tempo * 60;
    cin >> tempo;
    p.tempo += tempo;

    cout << "Il vincitore è " << p.nome
         << " con il tempo di "
         << p.tempo / 60 << " minuti e "
         << p.tempo % 60 << " secondi."
         << endl;

    return 0;
}
#include <iostream>
using namespace std;


struct partecipante_t {
    char    cognome[32];
    int     tempo;
};


/*
 *  @param lista:   array dei partecipanti
 *  @param max:     massimo numero di partecipanti
 *  @param n:       numero corrente di partecipanti
 *  @param cognome: stringa null-terminated col cognome del partecipante
 *  @return:        false se la lista è piena
 */
bool InserisciPartecipante(partecipante_t lista[], const int max, int &n, const char cognome[]) {
    if(n == max)
        return false;

    int i=0;
    for(i=0; i<n && strcmp(cognome, lista[i].cognome) > 0; i++) ;

    for(int j=n; j > i; j--)
        lista[j] = lista[j-1];

    strcpy(lista[i].cognome, cognome);

    return true;
}


void StampaElenco(const partecipante_t lista[], const int n) {
    cout << "Totale partecipanti: " << n << endl;

    for(int i=0; i<n; i++)
        cout << "- " << lista[i].cognome << endl;
}


void StampaPrimo(const partecipante_t lista[], const int n) {
    if(n == 0) {
        cout << "Che gara triste... neanche un partecipante..." << endl;
        return;
    }

    int m = 0;

    for(int i=1; i<n; i++)
        if(lista[i].tempo < lista[m].tempo)
            m = i;

    cout << "Il primo classificato è " << lista[m].cognome << " con un tempo di "
         << lista[m].tempo / 60 << " minuti e " << lista[m].tempo % 60 << " secondi." << endl;

}


void InserisciTempi(partecipante_t lista[], const int n) {
    int min, sec;

    for(int i=0; i<n; i++) {
        cout << "Inserisci il tempo per " << lista[i].cognome << " [min, sec]: ";

        cin >> min >> sec;
        lista[i].tempo = 60 * min + sec;
    }
}


int main() {
    int scelta;

    const int MAX_PART  = 10;
    partecipante_t lista_partecipanti[MAX_PART];
    int curr_part = 0;  // Numero di partecipanti nella lista

    while (true) {
        cout<<"Gestione classifica\n" ;
        cout<<"Menu\n" ;
        cout<<"1 Inserimento di un nuovo partecipante\n" ;
        cout<<"2 Stampa elenco partecipanti\n" ;
        cout<<"3 Gara\n" ;
        cout<<"4 Stampa primo classificato\n" ;
        cout<<"5 Uscita\n" ;
        cin>>scelta ;
        switch(scelta) {

            case 1:
                char cognome[32];
                cout << "Inserisci nominativo (cognome): ";
                cin >> cognome;

                if(!InserisciPartecipante(lista_partecipanti, MAX_PART, curr_part, cognome)) {
                    cout << "La lista è piena" << endl;
                } else {
                    cout << "Partecipante inserito" << endl;
                }

                break;

            case 2:
                StampaElenco(lista_partecipanti, curr_part);
                break;

            case 3:
                InserisciTempi(lista_partecipanti, curr_part);
                break;

            case 4:
                StampaPrimo(lista_partecipanti, curr_part);
                break;

            case 5:
                return 0;

            default:
                continue;
        } // Fine switch
    } // Fine while
    return 0 ;
}

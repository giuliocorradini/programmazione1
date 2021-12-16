#include <iostream>
#include <fstream>
using namespace std;

const char savefile[] = "coda.txt";

//Struttura dati
struct ring_t {
    char *utenti;
    int max;
    int head;
    int curr;           //number of current people in queue
};

void ring_init(ring_t &r) {
    r.utenti = nullptr;
    r.max = r.head = r.curr = 0;
}

void inizializza_coda(ring_t &r, const int n) {
    if(r.utenti != nullptr && r.curr != n)
        delete [] r.utenti;

    if(r.curr == n) {
        r.max = r.head = r.curr = 0;
        return;
    }

    r.max    =  (n>0) ? n           : 0;
    r.utenti =  (n>0) ? new char[n] : nullptr;

    r.head = 0;
    r.curr = 0;
}

void accoda_utente(ring_t &c, char u) {
    if(c.curr < c.max) {
        int tail = (c.head + c.curr) % c.max;

        c.utenti[tail] = u;
        c.curr++;
    }
}

void stampa_coda(const ring_t &c, ostream &out) {
    for(int i=0; i<c.curr; i++) {
        int wrapped_index = (c.head + i) % c.max;

        if(i!=0)
            cout << ' ';
        out << c.utenti[wrapped_index];
    }

    cout << endl;
}

bool salva_coda(ring_t &c) {
    ofstream f(savefile);

    if(!f)
        return false;

    f << c.curr << endl;
    stampa_coda(c, f);
    
    return static_cast<bool>(f);
}

bool carica_coda(ring_t &c) {
    ifstream f(savefile);

    if(!f)
        return false;

    int dimensione;
    f >> dimensione;

    inizializza_coda(c, dimensione);

    char servizio;
    for(int i=0; i<dimensione && f; i++) {
        f >> servizio;
        accoda_utente(c, servizio);
    }

    return static_cast<bool>(f);
}

bool servi_prossimo_utente(ring_t &c) {
    if(c.curr == 0)
        return false;

    c.head++;
    c.curr--;
    
    return true;
}

void anticipa_servizio(ring_t &c, char servizio) {
    int i = 0, j = 0;
    char *temp_coda = new char[c.curr];

    for(i=0; i<c.curr; i++) {
        int coda_index = (c.head + i) % c.max;
        if(c.utenti[coda_index] == servizio)
            temp_coda[j++] = servizio;
    }

    for(i=0; i<c.curr; i++) {
        int coda_index = (c.head + i) % c.max;
        if(c.utenti[coda_index] != servizio)
            temp_coda[j++] = c.utenti[coda_index];
    }

    delete [] c.utenti;
    c.utenti = temp_coda;
}

int main() {
	const char menu[] =
		"1. Reinizializza coda\n"
		"2. Accoda utente\n"
		"3. Stampa coda\n"
		"4. Salva coda\n"
		"5. Carica coda\n"
		"6. Servi prossimo utente\n"
		"7. Anticipa servizio\n"
		"8. Esci\n";

    ring_t coda = {.utenti = nullptr};
    int dimensione;
    char servizio;

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1:
            cout << "Inserisci la dimensione della coda: ";
            cin >> dimensione;
            inizializza_coda(coda, dimensione);
			break;
		case 2:
            cout << "A che servizio deve accedere l'utente? ";
            cin >> servizio;
            accoda_utente(coda, servizio);
			break;
		case 3:
            stampa_coda(coda, cout);
			break;
		case 4:
            if(salva_coda(coda))
                cout << "Salvato!" << endl;
            else
                cout << "Errore di salvataggio" << endl;
			break;
		case 5:
            if(carica_coda(coda))
                cout << "Coda caricata!" << endl;
            else
                cout << "Errore di caricamento" << endl;
			break;
		case 6:
            if(!servi_prossimo_utente(coda))
                cout << "Errore: non ci sono utenti in coda" << endl;
			break;
		case 7:
            cout << "Che servizio vuoi anticipare? ";
            cin >> servizio;

            anticipa_servizio(coda, servizio);
			break;
		case 8:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}

#include <iostream>
#include <fstream>
using namespace std;

typedef unsigned int uint;

const char *savefile = "crucipuzzle.txt";   //nome del file di salvataggio

struct puzzle_t {
    unsigned int dimensione;
    char *contenuto;
};

bool inizializza_puzzle(puzzle_t &puzzle, const unsigned int dim, istream &in) {
    if(puzzle.contenuto != nullptr)
        delete [] puzzle.contenuto;

    puzzle.dimensione = dim;
    puzzle.contenuto = new char[dim * dim];

    char c;
    for(uint i=0; i<dim*dim && in; i++) {
        in >> c;    //leggo un carattere dallo stream di input (cin o file)
                    //salta eventuali spazi bianchi
        
        if(c >= 'A' && c <= 'Z')
            puzzle.contenuto[i] = c;
        else
            puzzle.contenuto[i] = 'A';
    }

    return static_cast<bool>(in);   //ritorna lo stato dello stream
}

void stampa_puzzle(const puzzle_t &puzzle, ostream &out) {
    unsigned int tot_elementi = puzzle.dimensione * puzzle.dimensione;

    for(uint i=0; i<tot_elementi; i++) {
        if(i % puzzle.dimensione != 0)  //stampa spazio prima delle colonne > 0
            out << ' ';
        else if (i != 0)                //vai a capo quando stampi la prima colonna non della prima riga
            out << endl;

        out << puzzle.contenuto[i];
    }

    out << endl;
}

bool salva_puzzle(const puzzle_t &puzzle) { //CHECK: devo rendere parametrico il nome del file?
    ofstream f(savefile);

    if(!f)
        return false;

    f << puzzle.dimensione << endl;
    stampa_puzzle(puzzle, f);

    return true;
}

bool carica_puzzle(puzzle_t &puzzle) {
    ifstream f(savefile);

    if(!f)
        return false;

    uint dimensione;

    f >> dimensione;
    return inizializza_puzzle(puzzle, dimensione, f);
}

bool cerca_parola_verticale(const puzzle_t &puzzle, const char *parola) {
    uint word_l = strlen(parola);
    if(word_l == 0 || word_l > puzzle.dimensione)
        return false;

    uint plen = puzzle.dimensione * puzzle.dimensione;  //dimensione lineare del puzzle N*N

    for(uint i=0; i<plen; i++) {
        if(puzzle.contenuto[i] == parola[0]) {
            int j = i;
            uint k = 0;  //contatore parola

            // Ricerca verso il BASSO
            if((puzzle.dimensione - i / puzzle.dimensione + 1) >= word_l) {     //controllo di avere abbastanza lettere sotto

                for(k=0; k<word_l && j<(int)plen && puzzle.contenuto[j] == parola[k]; k++, j+=puzzle.dimensione);

                if(k == word_l) //ho verificato tutta la parola
                    return true;
            }

            // Ricerca verso l'ALTO
            if((i / puzzle.dimensione + 1) >= word_l) {
                j = i;
                for(k=0; k<word_l && j >= 0 && puzzle.contenuto[j] == parola[k]; k++, j-=puzzle.dimensione);

                if(k == word_l)
                    return true;
            }
        }
    }

    return false;
}

bool cerca_parola_globale(const puzzle_t &puzzle, const char *parola) {
    uint word_l = strlen(parola);
    if(word_l == 0)
        return false;

    uint p_linear = puzzle.dimensione * puzzle.dimensione;

    bool p_letters[26];

    //popola il set
    for(uint i=0; i<p_linear; i++)
        p_letters[puzzle.contenuto[i] - 'A'] = true;

    //confronta la parola col set
    for(uint i=0; i<word_l; i++)
        if(!p_letters[parola[i] - 'A'])
            return false;

    return true;
}

int main() {
    // Strutture dati
    puzzle_t puzzle = {0, nullptr};

    // appoggi
    int dimensione;
    char parola[11];

    // Costanti
	const char menu[] =
		"1. Reinizializza puzzle\n"
		"2. Stampa puzzle\n"
		"3. Salva puzzle\n"
		"4. Carica puzzle\n"
		"5. Trova parola in verticale\n"
		"6. Trova parola globalmente\n"
		"7. Esci\n";


    //  Stampa menù, elabora input
	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1:
            cout << "Inserisci la dimensione del puzzle: ";
            cin >> dimensione;

            cout << "Inserisci il contenuto del puzzle come sequenza di caratteri: ";
            inizializza_puzzle(puzzle, dimensione, cin);
			break;
		case 2:
            stampa_puzzle(puzzle, cout);
			break;
		case 3:
            salva_puzzle(puzzle);
			break;
		case 4:
            carica_puzzle(puzzle);
			break;
		case 5:
            cout << "Parola da cercare: ";
            cin >> parola;

            cout << endl;                                   //richiesto per il correttore
            if(cerca_parola_verticale(puzzle, parola))
                cout << "PRESENTE" << endl;
            else
                cout << "ASSENTE" << endl;
			break;
		case 6:
            cout << "Parola da cercare: ";
            cin >> parola;

            cout << endl;
            if(cerca_parola_globale(puzzle, parola))
                cout << "PRESENTE" << endl;
            else
                cout << "ASSENTE" << endl;
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}

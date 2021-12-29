#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;


const int NOME_MAX_LEN = 32;
const char *SAVEFILE = "carnet.txt";

struct biglietto_t {
    char *nome;
    unsigned int progressivo;
};

// Collection of biglietto_t's of variable length
struct carnet_t {
    struct biglietto_t *biglietti;
    int len;
    int max;
};

void biglietto_init(biglietto_t &b) {
    if(b.nome != nullptr)   //CHECK: serve davvero?
        delete [] b.nome;

    b = {.nome=nullptr, .progressivo=0};
}

void carnet_init(carnet_t &c) {
    c = {.biglietti=nullptr, .len=0, .max=32};
}

/*
 *  Alloca un array di dimensioni doppie se ho esaurito il numero massimo
 *  di biglietti.
 */
void carnet_realloc(carnet_t &c) {
    biglietto_t *dst_biglietti = new biglietto_t[c.max * 2];
    c.max *= 2;

    for(int i=0; i<c.len; i++)
        dst_biglietti[i] = c.biglietti[i];
    
    delete [] c.biglietti;
    c.biglietti = dst_biglietti;
}

bool carnet_is_full(const carnet_t &c) {
    return c.max == c.len;
}

void vendi_biglietto(carnet_t &c, const char *proprietario, const int numero) {
    //prepara biglietto
    biglietto_t b;
    biglietto_init(b);

    b.nome = new char[NOME_MAX_LEN];
    strncpy(b.nome, proprietario, NOME_MAX_LEN);

    b.progressivo = numero;

    //inserisci nel carnet
    if(carnet_is_full(c)) {
        carnet_realloc(c);
    }

    c.biglietti[c.len++] = b;
}

void stampa_biglietti(const carnet_t &c, const int n, ostream &out) {
    for(int i=0; i<n; i++) {
        out << c.biglietti[i].nome << " " << c.biglietti[i].progressivo << endl;
    }
}

bool salva_biglietti(const carnet_t &c, const int n) {
    ofstream f(SAVEFILE);

    if(!f)
        return false;

    f << c.len << endl;
    stampa_biglietti(c, n, f);

    return static_cast<bool>(f);
}

bool carica_biglietti(const carnet_t &c, const int n) {
    ifstream f(SAVEFILE);

    if(!f)
        return false;

    int dimensione;
    f >> dimensione;

    

    return static_cast<bool>(f);
}


int main() {
	const char menu[] =
		"1. Vendi biglietto\n"
		"2. Stampa biglietti venduti\n"
		"3. Salva biglietti venduti\n"
		"4. Carica biglietti venduti\n"
		"5. Stampa vincitore\n"
		"6. Stampa primi n vincitori\n"
		"7. Esci\n";

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			return 0;
		default:
			cout<<"Scelta errata"<<endl;
		}
	}

	return 1;
}
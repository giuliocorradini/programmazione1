#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;

const char savefile[] = "matrice_parole.dat";

typedef char * word_t;

struct wmatrix_t {
    word_t *words;
    int rows;
    int cols;
};

void wmatrix_default(wmatrix_t &m) {
    m.words = nullptr;
    m.rows = 0;
    m.cols = 0;
}

void wmatrix_init(wmatrix_t &m, int rows, int cols) {
    //  Clear previously stored words
    if(m.words != nullptr) {
        int elements = m.rows * m.cols;
        for(int i=0; i<elements; i++)
            if(m.words[i] != nullptr)
                delete m.words[i];

        delete [] m.words;
    }

    //  Allocate array
    m.words = new word_t[rows * cols];
    for(int i=0; i<rows*cols; i++)  m.words[i] = nullptr;
    m.rows = rows;
    m.cols = cols;
}

bool sostituisci_parola(wmatrix_t &m, char *p, const int i, const int j, const bool from_stdin) {
    int len = strlen(p) + 1;
    char *dyn_p;

    if(from_stdin) {
        dyn_p = new char[len];
        strcpy(dyn_p, p);
    } else {
        dyn_p = p;
    }

    if(i >= m.rows || j >= m.cols)
        return false;                   //invalid index

    int index = i*m.cols + j;
    if(m.words[index] != nullptr)
        delete [] m.words[index];

    m.words[index] = dyn_p;

    return true;
}

void stampa_matrice(const wmatrix_t &m) {
    int m_len = m.cols * m.rows;
    int *larghezze = new int[m.cols];
    for(int i=0; i<m.cols; i++)  larghezze[i] = 0;

    //  Calcola larghezza di ciascuna colonna
    for(int i=0; i<m_len; i++) {
        if(m.words[i] == nullptr)
            continue;

        int str_len = strlen(m.words[i]);
        if(larghezze[i % m.cols] < str_len)
            larghezze[i % m.cols] = str_len;
    }

    for(int i=0; i<m_len; i++) {
        if(i % m.cols == 0 && i != 0)
            cout << endl;
        
        cout << setfill(' ') << setw(larghezze[i % m.cols]) << (m.words[i] ? m.words[i] : "") << ' ';
    }

    cout << endl;

    delete [] larghezze;
}

bool salva_matrice(const wmatrix_t &m) {
    ofstream f(savefile);

    if(!f)
        return false;

    int total;
    for(int i=0; i<m.rows * m.cols; i++)
        if(m.words[i] != nullptr)
            total++;

    f.write((char *)&m.rows, sizeof(int));
    f.write((char *)&m.cols, sizeof(int));
    f.write((char *)&total, sizeof(int));

    for(int i=0; i<m.rows * m.cols; i++) {
        if(m.words[i] == nullptr)
            continue;

        int y = i / m.cols;
        f.write((char *)&y, sizeof(int));
        int x = i % m.cols;
        f.write((char *)&x, sizeof(int));

        int l = strlen(m.words[i]);
        f.write((char *)&l, sizeof(int));

        f.write(m.words[i], l);
    }

    bool status = static_cast<bool>(f);
    f.close();
    return status;
}

bool carica_matrice(wmatrix_t &m) {
    ifstream f(savefile);

    if(!f)
        return false;

    int rows, cols, total;

    f.read((char *)&rows, sizeof(int));
    f.read((char *)&cols, sizeof(int));
    f.read((char *)&total, sizeof(int));

    wmatrix_init(m, rows, cols);

    for(int i=0; i<rows * cols && i < total; i++) {
        int y, x;
        f.read((char *)&y, sizeof(int));
        f.read((char *)&x, sizeof(int));

        cout << "posizione: " << y << " " << x << endl;

        int slen;
        f.read((char *)&slen, sizeof(int));

        cout << "lunghezza: " << slen << endl;
        
        char *p = new char[slen + 1];
        f.read(p, slen);

        p[slen] = '\0';

        cout << "parola: " << p;

        sostituisci_parola(m, p, y, x, false);
    }

    bool status = static_cast<bool>(f);
    f.close();
    return status;
}

int main()
{
	const char menu[] =
		"1. Sostituisci parola\n"
		"2. Stampa matrice\n"
		"3. Salva matrice\n"
		"4. Carica matrice\n"
		"5. Scambia parole\n"
		"6. Scambia con parola di lunghezza minima\n"
		"7. Esci\n";

    wmatrix_t m;
    wmatrix_default(m);
    wmatrix_init(m, 3, 2);

    char parola[32];
    int riga, colonna;

	while (true) {
		cout<<menu<<endl;
		int scelta;
		cin>>scelta;

		cout<<endl ; // per il corretto funzionamento del tester

		switch (scelta) {
		case 1:
            cout << "Inserisci la parola: ";
            cin >> parola;
            cout << "Inserisci riga e colonna separate da spazio: ";
            cin >> riga >> colonna;
            if(!sostituisci_parola(m, parola, riga, colonna, true))
                cout << "Errore di inserimento. Indice non valido." << endl;
			break;
		case 2:
            stampa_matrice(m);
			break;
		case 3:
            if(salva_matrice(m))
                cout << "salvato correttamente" << endl;
            else
                cout << "errore..." << endl;
			break;
		case 4:
            if(carica_matrice(m))
                cout << "caricato correttamente" << endl;
            else
                cout << "errore..." << endl;
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
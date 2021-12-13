/*
Contenitore

Un Contenitore e' in grado di contenere elementi in numero limitato (la
capienza del contenitore). Ciascun elemento ha un nome che consiste in
una lettera (minuscola) dell'alfabeto. Piu' elementi di un contenitore
possono avere lo stesso nome. Implementare il contenitore mediante il
tipo di dato struct. Le operazioni che possono essere effettuate sul
contenitore sono le seguenti:

.	Inizializza(N);
Inizializza il contenitore con capienza pari ad N elementi. Il
contenitore e' vuoto. L'eventuale contenuto precedente viene perso.

.	Inserisci(p)
Inserisce un elemento avente nome p.

.	Estrai(p)
Estrae dal contenitore tutti gli elementi aventi nome p.

.	Modifica(N)
Modifica la capienza del contenitore. Dopo la modifica il contenitore
ha capienza N e contenuto identico a quello originario. Affinche'
l'operazione abbia successo, il numero di elementi contenuti nel
contenitore deve essere minore od uguale ad N.

.	capienza()
Ritorna la capienza del contenitore.

.	quanti()
Ritorna il numero degli elementi presenti nel contenitore.

.	stampa()  

Stampa il contenuto del Contenitore. LŽ¢uscita ha la forma seguente:
		<a:3, d:1, s:5>
In questo esempio, nel contenitore sono presenti tre elementi di nome
'a', uno di nome 'd' e cinque di nome 's'.

Nella soluzione e' contenuto anche un main, che potete eventualmente
utilizzare per testare le funzioni nella vostra soluzione.
*/

#include <iostream>
using namespace std;

const int ALPHABET = 26;
struct contenitore {
    int elementi[ALPHABET];
    int capienza;               //capienza massima
};

enum container_error_t {
    CONTAINER_OK        = 0,
    CONTAINER_FULL,
    CONTAINER_OUT_OF_BOUNDS,
    CONTAINER_OVERFLOW,
    CONTAINER_MAX_ERROR
};

int quanti(struct contenitore &c) {
    int totale = 0;
    for(int i=0; i<ALPHABET; i++)
        totale += c.elementi[i];

    return totale;
}

int capienza(struct contenitore &c) {
    return c.capienza - quanti(c);
}

void stampa(struct contenitore &c) {
    bool primo = true;

    cout << "<";
    for(int i=0; i<ALPHABET; i++)
        if(c.elementi[i]) {
            if(!primo)
                cout << ", ";
            cout << 'a' + i << ":" << c.elementi[i];
            primo = false;
        }

    cout << ">" << endl;
}

void decodifica_errore(enum container_error_t e) {
    switch(e) {
        case CONTAINER_FULL:
            cout << "Il contenitore non può accogliere altri elementi" << endl;
            break;
        case CONTAINER_OUT_OF_BOUNDS:
            cout << "L'elemento specificato non fa parte del dominio del contenitore" << endl;
            break;
        case CONTAINER_OVERFLOW:
            cout << "Ci sono troppi elementi per ridurre la capienza massima" << endl;
            break;
        default:
            //do nothing
            break;
    }
}

/*
 * Inizializza il contenitore con capienza pari ad N elementi.
 * Il contenitore e' vuoto. L'eventuale contenuto precedente viene perso.
 */
void Inizializza(struct contenitore &c, int capienza) {
    for(int i=0; i<ALPHABET; i++)
        c.elementi[i] = 0;

    c.capienza = capienza >= 0 ? capienza : 0;
}

/*
 * Inserisce un elemento avente nome p.
 */
enum container_error_t Inserisci(struct contenitore &c, char p) {
    if(p - 'a' >= ALPHABET)
        return CONTAINER_OUT_OF_BOUNDS;

    if(capienza(c) <= 0)
        return CONTAINER_FULL;

    c.elementi[p]++;
    return CONTAINER_OK;
}

/*
 * Estrae dal contenitore tutti gli elementi aventi nome "p".
 * 
 */
enum container_error_t Estrai(struct contenitore &c, char p, int &elem) {
    if(p - 'a' >= ALPHABET)
        return CONTAINER_OUT_OF_BOUNDS;
    
    return c.elementi[p];
}

/*
 * Modifica la capienza del contenitore. Dopo la modifica il contenitore
 * ha capienza N e contenuto identico a quello originario. Affinche'
 * l'operazione abbia successo, il numero di elementi contenuti nel
 * contenitore deve essere minore od uguale ad N.
 */
enum container_error_t Modifica(struct contenitore &c, int nuova_capienza) {
    if(quanti(c) > nuova_capienza)
        return CONTAINER_OVERFLOW;

    c.capienza = nuova_capienza;
    return CONTAINER_OK;
}


int main() {
    struct contenitore cont;
    container_error_t err;

	const char Menu[] = 
	    "\nComandi disponibili:\n"
	    "\ti - per inserire un elemento nel contenitore\n"
	    "\te - per estrarre elementi dal contenitore\n"
	    "\tc - per modificare la capienza del contenitore\n"
	    "\tf - per informazioni sul contenitore\n"
	    "\tt - per terminare\n";
	
	cout<< "Inizializzazione contenitore.\n";
	cout<< "Immetterne la capienza (e premere Invio): ";
	int n;
	cin>>n;
	decodifica_errore(Inizializza(cont, n));
	cout<<endl;

	while(true) {
	    char comando;

	    stampa(cont);
	    cout<<Menu<<"\n\nImmettere comando e premere Invio: ";
	    cin>>comando; // 'consumiamo' il precedente newline

	    switch (comando) {
	    case 'i': {
		char p;
		cout<<"Inserisci nome elemento ";
		cin>>p;
		decodifica_errore(Inserisci(cont, p));
		break;
	    }
	    case 'e': {
		char p;
		cout<<"Inserisci nome elemento ";
		cin>>p;
        int num_elem;
		decodifica_errore(err = Estrai(cont, p, num_elem));
        if(err == CONTAINER_OK)
            cout << "Estratti " << num_elem << " elementi" << endl;
		break;
	    }
	    case 'c': {
		int i;
		cout<<"Inserisci nuova capienza (e premi Invio): ";
		cin>>i;
		decodifica_errore(Modifica(cont, i));
		break;
	    }
	    case 'f': 
		cout<<"Capienza: "<<capienza(cont)<<"\tElementi: "
		    <<quanti(cont)<<endl;
		break;
	    case 't': 
		return 0;
	    default: 
		cout<< "Comando non valido\n";
	    }
	}
	return 0;
}

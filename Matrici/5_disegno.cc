/*
 * I parte
 *
 * Partendo dal frammento di programma di seguito fornito, scrivere un
 * programma che faccia apparire e permetta di spostare un puntatore,
 * denotato dal carattere X, all'interno di una tavola di caratteri
 * quadrata e costituita da spazi. Il puntatore, che all'inizio si
 * trova al centro della tavola, si sposta nelle quattro possibili
 * direzioni alla pressione di uno di quattro tasti predefiniti. Ad
 * esempio, nel caso di tavola di dimensioni 6x6, l'output iniziale
 * sarebbe il seguente:
 *
 * j->sinistra, l->destra, i->alto, k->basso
 * q->esci
 *
 *      
 *     
 *   X  
 *     
 *
 *
 * Se si premesse il tasto l, il nuovo output sarebbe:
 *
 * j->sinistra, l->destra, i->alto, k->basso
 * q->esci
 *
 *      
 *     
 *    X  
 *     
 *
 *
 * Per far si che nel terminale appaia solo l'output del programma, si
 * puo' cancellare il contenuto del terminale stesso prima di
 * ristampare il nuovo output. Per farlo si puo' utilizzare, ad
 * esempio, la funzione:
 * system("clear");
 * che invoca semplicemente il comando clear.
 * 
 * Il puntatore puo' spostarsi solo all'interno della tavola, quindi
 * per esempio, una volta raggiunto il bordo destro, non e' possibile
 * farlo spostare ancora piu' a destra.
 *
 * Il ridisegno della tavola e l'aggiornamento del suo contenuto
 * devono essere realizzati all'interno di due funzioni.
 *
 *
 * II parte
 *
 * Aggiungere altre due modalita' del puntatore rispetto a quella di
 * semplice spostamento. La prima delle due nuove modalita' sia quella
 * di disegno, e la seconda quella di cancellazione. Definire il tasto
 * da premere per passare in ciascuna delle tremodalita'.
 * 
 * Nella modalita' di disegno il simbolo del puntatore deve diventare
 * un +. Inoltre, in ogni posizione da esso occupato, il puntatore
 * deve disegnare un *.  Ad esempio, supponiamo che il puntatore si
 * trovi al centro della tavola e sia in modalita' di solo
 * spostamento. Se lo si fa passare in modalita' disegno e lo si sposta
 * verso sinistra si ottiene:
 *
 * j->sinistra, l->destra, i->alto, k->basso
 * u->disegna, o->cancella, n->solo sposta
 * q->esci
 *
 *      
 *     
 *  +*  
 *     
 *
 *
 * Se poi lo si sposta ad esempio verso l'alto, si ottiene:
 *
 * j->sinistra, l->destra, i->alto, k->basso
 * u->disegna, o->cancella, n->solo sposta
 * q->esci
 *
 *      
 *  +   
 *  **  
 *     
 *
 *
 * E cosi' via. Infine, nella modalita' di cancellazione il simbolo
 * del puntatore deve divenire un -. Nella modalita' di cancellazione
 * il puntatore ritrasforma in uno spazio l'eventuale * presente nella
 * posizione da esso occupata.
 *
 * La soluzione dell'esercizio e' nel file sol_car_codici_immediato.cc
 *
 *
 * Estensioni:
 *. salvataggio e caricamento disegno
 *. spostamento puntatore mediante tasti cursore
 *. stampa di una cornice attorno all'area di disegno
*/

/*
 * Segue il frammento di programma da cui partire
 *
 * Per lo svolgimento dell'esercizio non e' di nessuna importanza
 * capire come si ottiene il cambio di modalita' del terminale.  I
 * dettagli su tali operazioni si vedranno in corsi futuri. Quello che
 * va fatto e' solo scrivere le righe mancanti!
 *
 */

#include <iostream>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

const int CANVAS_X  = 6;    //Canvas x size
const int CANVAS_Y  = 6;    //Canvas y size

const bool USE_SYSTEM_CLEAR = false;    //set to true if you want to use system's clear command to clear output
                                        //ANSI code will be used otherwise (faster option)

enum cursor_mode_t {
    DRAWING,
    ERASING,
    MOVING
};

struct cursor_t {
    int x;
    int y;
    cursor_mode_t mode;
};

/*
 * Configura il terminale in modo non canonico
 */
void vai_in_modo_non_canonico() 
{
    struct termios nuovo;
    if (tcgetattr(STDIN_FILENO, &nuovo) < 0) {
	cout<<"Salvataggio modo terminale fallito"<<endl;
	exit(1);
    }

    nuovo.c_lflag &= ~ICANON;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &nuovo) < 0) {
	cout<<"Settaggio modo terminale fallito"<<endl;
	exit(1);
    }

}

void salva_modo_terminale(termios &modo)
{
    if (tcgetattr(STDIN_FILENO,  &modo) < 0) {
	cout<<"Salvataggio modo terminale fallito";
	exit(1);
    }
}

void assegna_modo_terminale(termios &modo)
{
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &modo) < 0) {
	cout<<"Salvataggio modo terminale fallito";
	exit(1);
    }
}


void clear_output() {
    if (USE_SYSTEM_CLEAR)
        system("clear");
    else
        cout << "\x1b[2J";
}

void print_commands() {
    cout << "j->sinistra, l->destra, i->alto, k->basso" << endl
         << "u->disegna, o->cancella, n->solo sposta" << endl
         << "q->esci" << endl;
}

/*
 *  Display update routine. Clears display, prints legend, cursor and canvas.
 *  @param canvas: a pointer to the matrix representing the canvas
 *  @param cur: current position of the cursor 
 */
void update_display(const char canvas[][CANVAS_X], const cursor_t cur) {
    clear_output();
    print_commands();

    for(int i=0; i<CANVAS_Y; i++) {
        for(int j=0; j<CANVAS_X; j++) {
            if(cur.x == j && cur.y == i) {    //print cursor position
                switch (cur.mode) {
                case MOVING:
                    cout << "X";
                    break;
                case DRAWING:
                    cout << "+";
                    break;
                case ERASING:
                    cout << "-";
                    break;
                }
            } else if (canvas[i][j] == '*') {
                cout << '*';
            } else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

void update_canvas(char canvas[][CANVAS_X], const cursor_t cursor) {
    if(cursor.mode == DRAWING)
        canvas[cursor.y][cursor.x] = '*';
    else if(cursor.mode == ERASING)
        canvas[cursor.y][cursor.x] = '\x00';    //any byte should be ok
}


int main()
{
    termios vecchio_modo_terminale;
    // si salva la modalita' corrente per ripristinarla al termine del
    // programma
    salva_modo_terminale(vecchio_modo_terminale);

    vai_in_modo_non_canonico();
    
    
    // qui va il vostro codice
    char canvas[CANVAS_Y][CANVAS_X] = {};   //init to zeroes
    cursor_t cursor = {0, 0, MOVING};

    char cmd;
    do {
        //Print canvas
        update_display(canvas, cursor);

        //Get key
        cin >> cmd;

        //Decode key
        switch(cmd) {
            case 'i':   //up
                if (cursor.y > 0) {
                    cursor.y--;
                    update_canvas(canvas, cursor);
                }
                break;
            case 'k':   //down
                if(cursor.y < CANVAS_Y - 1) {
                    cursor.y++;
                    update_canvas(canvas, cursor);
                }
                break;
            case 'j':   //left
                if(cursor.x > 0) {
                    cursor.x--;
                    update_canvas(canvas, cursor);
                }
                break;
            case 'l':   //right
                if(cursor.x < CANVAS_X - 1) {
                    cursor.x++;
                    update_canvas(canvas, cursor);
                }
                break;
            case 'u':   //draw
                cursor.mode = DRAWING;
                update_canvas(canvas, cursor);
                break;
            case 'o':   //erase
                cursor.mode = ERASING;
                update_canvas(canvas, cursor);
                break;
            case 'n':   //move
                cursor.mode = MOVING;
                break;
            default:    //other
                break;
        }
    } while(cmd != 'q');


    // qui il terminale viene riportato nella modalita' precedente
    assegna_modo_terminale(vecchio_modo_terminale);

    return 0;
}

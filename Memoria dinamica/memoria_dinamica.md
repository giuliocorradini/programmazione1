# Memoria dinamica

Un segmento della memoria chiamato **heap** (o memoria libera, memoria dinamica) mi permette
di allocare spazio di memoria arbitrariamente e di grandezza arbitraria durante l'esecuzione
del programma.

Gli oggetti allocati in memoria dinamica sono detti dinamici.

Faremo principalmente uso degli array dinamici.

In C si usava *malloc*.

## new

C++ riserva una parola per l'allocazione dinamica: `new`.

Per allocare un vettore di dimensione scelta dall'utente a tempo di runtime posso scrivere:

```
new int[a];
```

quindi la dimensione non deve più essere una constexpr.

L'espressione sopra alloca memoria, ma non posso utilizzare lo spazio perché non ho ancora
associato l'indirizzo (quello che ritorna new) alla variabile.

## Puntatori

Sono variabili che hanno come valore un indirizzo di memoria. Un puntatore non è diverso da un intero.

Il qualificatore const per i puntatori inibisce la modifica dell'area di memoria target.

```
const int *a = <indirizzo>;
```

Posso anche mettere un secondo const se voglio che il valore della variabile di tipo puntatore non sia
modificato (un classico const).

Per accedere all'ennesimo elemento di un'area di memoria usando un puntatore posso usare la notazione
con le parentesi quadre come avveniva per gli array statici.

### Dominio

Un puntatore ha per valori un sottinsieme dei numeri naturali. Se contiene 0 per convenzione viene
detto puntatore nullo (NULL in C).

Se un puntatore contiene 0 non punta a nessuna zona di memoria utile oppure abbiamo scelto di non
assegnarlo a niente.

## Tempo di vita

Un variabile allocata dinamicamente esiste fino alla fine del programma, da quando è stata dichiarata,
oppure finché non libero esplicitamente quella zona di memoria.

Se perdo il puntatore a una zona di memoria senza deallocarla è memoria occupata che viene liberata
solo quando termino il programma. Questo problema è detto memory leak.

## delete

Per deallocare un array posso usare la keyword delete:

```
int *dynVect = new int[N];
delete [] dynVect;
```

Se provo a deallocare `nullptr` non succede niente. Però se provo a deallocare due volte la stessa zona
di memoria allora il programma mi darà un errore.

Attenzione che `delete` non mette automaticamente il valore del puntatore a `nullptr`.

Liberare esplicitamente la memoria appena prima di terminare il programma non è necessario ma **caldamente
consigliato**. Se volessi convertire il mio codice in una funzione potrei avere un problema di memory leak.

Non posso deallocare parte della memoria che ho riservato.

## Passaggio alle funzioni

Si usa la stessa sintassi usata per gli array statici, oppure uso la notazione con l'asterisco. La prima
è più chiara per quanto riguarda gli array.

## Allocazione in-function

```c++
int * fun() {
    int *p = new int;
    return p;
}
```

è valido perché viene deallocato solo il puntatore all'oggetto intero, mentre l'area di memoria
permane nello heap.

Per ritornare dimensione del vettore e vettore stesso allocati nella funzione posso:
 
- usare una variabile riferimento per passare dimensione o vettore

- void e passo entrambi per riferimento

- struct come valore di ritorno con puntatore e dimensione

## Riferimento a puntatore

*unsigned int* dal punto di vista logico. È un riferimento (indirizzo) a un puntatore (indirizzo).

## Effetti collaterali

Siccome più puntatori possono puntare allo stesso oggetto, possono esserci effetti collaterali.

### dangling reference o pending pointer

Il puntatore punta a una zona di memoria in cui l'oggetto non è allocato.

Se opero con un pending pointer ho un *undefined behaviour*. Un bug non ripetibile è difficile da trovare.

Se un programma ha un memory leak (esaurimento non aspettato della memoria, causato dalla non deallocazione
degli oggetti dinamici inutilizzati) potrebbe essere killato dal sistema operativo se riempie tutta la RAM e tutta lo swap.

```c++
while(true) {
    int *p = new int[100000];
    for(int i=0; i<100000; i++)
        p[i] = i;
}
```

[E se provassi ad allocare troppa memoria? - Jacob Sorber](https://www.youtube.com/watch?v=Fq9chEBQMFE)

## Array di struct dinamico

Perfettamente lecito, tant'è vero che una struct è un normalissimo tipo di dato.

```c++
struct persona_t {
    char *nome;
    char *cognome;
    float stipendo;
};

int main() {
    int N;
    cin >> N;

    struct persona_t persone[] = new persona_t[N];
}
```


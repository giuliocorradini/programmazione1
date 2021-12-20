# Liste

Strutture dati dinamiche. Ci sono algoritmi che risolvono problemi in modo
molto efficace usando una struttura dati che cambia dimensione dinamicamente.

Esempio: *memorizza e stampa una serie di valori, il cui numero non è noto a priori*

Quanto costa usare un array dinamico e riallocarlo? O(n). Siccome lo faccio ogni
tanto possiamo considerare il costo ammortizzato O(1).

## Idea

L'operatore `new` può allocare anche un singolo oggetto, da solo in memoria. Così
quando devo estrarlo mi basta deallocare solo lui e non tutti i dati.

Dove salvo l'indirizzo di tutti gli elementi che alloco? In una variabile locale o
globale di tipo puntatore.

```c++
oggetto_t *x = new oggetto_t;
```

Per implementare una lista userò una struct che rappresenta ogni elemento della lista e
contiene un campo *informazione* con il valore dell'i-esimo elemento e un puntatore
all'elemento successivo della lista.
Se il puntatore contiene `nullptr` allora non ha alcun elemento successivo.

Il primo elemento è detto *head* o testa, l'ultimo è *tail* o coda.
Parlare di coda o lista è simile, ma nelle liste si può fare inserimento e rimozione
ovunque mentre nella coda si può solo inserire in fondo ed estrarre in testa.

Distinguiamo anche *single linked list* se ogni elemento contiene solo il puntatore
al successivo.

Una *double linked list* è una lista con due puntatori: all'elemento precedente e
all'elemento successivo.

Riordinare la lista costa di solito O(n logn).

In C++ nella libreria standard c'è il tipo di dato `<list>`.

## Vantaggi e svantaggi

Un array occupa tipicamente meno spazio della lista (quasi la metà).
L'inserimento in coda costa O(1), ma l'inserimento in testa e in mezzo
costa O(n).

Le liste invece permettono inserimento in testa e in mezzo in O(1) a patto
che si conosca l'indirizzo dell'elemento successivo.

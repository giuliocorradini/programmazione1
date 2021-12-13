# Matrici

Le matrici sono tabelle ordinate di elementi.
Normalmente noi lavoriamo su matrici bidimensionali, ma possono avere qualsiasi n-dimensione.

Una matrice n x m ha n righe, m colonne.

## Definizione

Come per gli array uso la notazione con parentesi quadre, specifico tutte le dimensioni.

```c++
double matrice[4][3];
```

Ho definito una matrice 4x3: 4 righe, 3 colonne di elementi double.

Posso inizializzare la matrice contestualmente alla definizione. La notazione è quella di un
"array innestato"

```c++
double matrice[][3] = {
    {1, 2, 3},
    {4, 5, 7}
};
```

Se inizializzo nella definizione posso **omettere** la dimensione delle righe, ma quella delle colonne è
richiesta.

Per lavorare sulle matrici, ci si lavora con due cicli for innestati. Il for interno si muove
più velocemente e lavora sulle colonne, il ciclo esterno è più lento e scansiona le righe.

## Stampa di una matrice

Primo modo (canonico) di accedere a una matrice. Doppio loop innestato.

```c++
//stampare una matrice
for(int i=0; i<RIGHE; i++) {
    for(int j=0; j<COLONNE; j++) {
        cout << mat[i][j] << " ";
    }
    cout << endl;
}
```

## Layout in memoria

Le matrici sono salvate come array, memorizzate come righe continue. Il C è un linguaggio **row major**, per
questo il primo indice specificato è l'indice di riga.

## Passaggio alle funzioni

Posso passare una singola riga alla funzione (vedi l'esempio 4).

Altrimenti posso passare la matrice, specificando però la dimensione delle colonne.

## Linearizzazione matrice

L'indirizzo di ogni elemento è univocamente `indirizzo_matrice + riga * num_colonne + colonna`

## Array di stringhe

Equivalente a una matrice di caratteri.

```c++
char giorni[7][11] = {
    "lunedì",
    "martedì",
    "mercoledì",
    "giovedì",
    "venerdì",
    "sabato",
    "domenica"
};
```

Le stringhe non riempiono la dimensione massima... quello che ci sta dopo è spazio sprecato.
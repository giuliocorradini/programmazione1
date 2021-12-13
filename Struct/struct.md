# Struct

## Passaggio

Vengono passate per valore alle funzioni (non per riferimento).

## Inizializzazione

La struct deve essere inizializzata con i campi in ordine.

Inoltre l'assegnazione tra struct copia ogni singolo valore.

Non è consentito assegnare una struttura di tipo diverso a un'altra, anche se hanno
gli stessi campi dello stesso tipo. Devono avere lo stesso identificatore di tipo.

## Array nella struct

L'unico caso in cui viene eseguita la deep copy dell'array, è quando questo
è contenuto in una struct. Anche se l'array è a più dimensioni viene TUTTO
copiato.

Quindi per copiare un'array senza ricorrere a un ciclo mi basta incapsularlo in una struct.

```c++
struct frutto {
    char nome[20];
    float peso, diametro;
};
```

## Array di struct

```c++
struct coord {int x, y};
coord vett[10];


//Accesso agli elementi
vett[2].x = 3;
```
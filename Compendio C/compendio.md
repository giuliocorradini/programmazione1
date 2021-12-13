# Compendio sul C

Spesso non è possibile usare un linguaggio "as-is" ma si usa una libreria standard.

Nel caso del C/C++ usiamo ad esempio `iostream`.

Una libreria è una collezione di funzioni, macro, costanti etc. che può essere inclusa
attraverso il suo file header.

## output

In C normale non ci sono cin, cout ma si usano le funzioni dalla libreria `stdio.h`, `printf`
e `scanf`.

Printf ha un numero variabile di parametri.

## Variadic functions

Sono funzioni che accettano un numero variabile di elementi. Non scrivo un prototipo per ogni
combinazione possibile.

Si possono definirle sia in C che in C++. Si usa un'estensione della sintassi vista fin'ora.
Per manipolare i parametri variadici formali si usano delle funzioni di libreria.

## << internals

L'operatore << inferisce il tipo di dato dalla variabile che gli passiamo.

## scanf

Attenzione alla dimensione dei dati

```c++
char a;
scanf("%d", &a);    //corruzione della memoria

scanf("%d", a);     //errore logico e di corruzione della memoria se il compilatore non controlla
```

## Qualificatore const

```c++
#define a 5
```

All'inizio il C non aveva le costanti, quindi si usavano le direttive al preprocessore `#define`.
Macro e const sono diverse, infatti è il compilatore che ogni volta che trova il valore a (ad esempio),
va a sostituirlo con 5.

## struct ed enum

Ci sono anche in C ma quando definisco devo comunque ripetere *struct* e *enum*.

Per evitare di farlo si fa `typedef`, ovvero definisco un sinonimo di un tipo di dato.

```c++
typedef unsigned int u_int;
u_int a;


typedef struct persona Persona;
Persona p;

typedef enum colore colore_t;
color_t c;
```

Posso anche scrivere una struct/enum anonima e fare un typedef contestuale

```c++
typedef struct {
    int x;
    int y;
} point_t;
```

typedef migliora la leggibilità e permette di sostituire nel programma i nomi di basso livello
con dei nomi più significativi.

## Memoria dinamica

Si possono usare le funzioni `malloc` etc. contenute nella libreria `stdlib.h`.
malloc ritorna sempre un `void *`, quindi bisogna fare il cast al tipo di puntatore corretto.

Attenzione che `malloc` lavora più a basso livello rispetto a `new`. malloc alloca sequenze di
byte quindi dovrò specificare la dimensione, ad esempio con `sizeof(int) * DIM`

`free` dealloca l'indirizzo della zona di memoria da deallocare.

## Compilare

Si compila con `gcc`, il suffisso tipico del C standard è `.c`.

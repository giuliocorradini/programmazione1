# Algoritmi

Un algoritmo viene progettato partendo dal problema che devo risolvere, e codificato con un linguaggio
di programmazione.

Ha tre proprietà:

- deve essere eseguibile

- non ambiguo (per la macchina, quindi un linguaggio naturale non andrebbe bene)

- deve terminare

è anche desiderabile che l'algoritmo sia efficiente e occupi poco spazio di memoria.

L'algoritmo dovrebbe essere deterministico, però alcuni sono volutamente non deterministici come
le reti neurali che sono addestrate in modo stocastico. Risolvo lo stesso problema in modo più
approssimato ma più efficiente.

## Equivalenza

Due algoritmi sono equivalenti (visti come black box) se hanno lo stesso dominio di input, dominio di output,
e in corrispondenza degli stessi valori in input producono differenti valori in output.

L'efficienza dei due algoritmi può essere diversa.

## Costo computazionale

L'efficienza in termini di tempo di esecuzione dell'algoritmo. Dipende dal numero di passi che devo
effettuare.

Il costo computazionale è valutato per un numero di elementi che tende all'infinito. Inoltre dipende
dall'insieme di operazioni elementari che posso eseguire, ad esempio una somma e una moltiplicazione
richiedono almeno due passi ma usando l'istruzione `FMA` (Fused-Multiply ADD, presente negli instruction set AVX2+) mi
permette di fare entrambe le operazioni in un ciclo di clock.

[Intel Advanced Vector Extensions Programming Reference](https://www.intel.com/content/dam/develop/external/us/en/documents/36945)

## Costanti di tempo

Supponiamo di avere due algoritmi che risolvono lo stesso problema.

- A ha complessità N, ci mette 20 passi

- B ha complessità N^2 e ci mette 2 passi per operazione

il più veloce sarà comunque A, che già con 10 elementi si equivale con B.

## Ordine di costo

### O grande

Dato il numero N di elementi su cui l'algoritmo lavora, dirò che l'algoritmo è di ordine O(N)
se esiste una costante c tale che la complessità dell'algoritmo cresce velocemente almeno tanto quanto N.

Misura efficace per confrontare gli algoritmi.

### Casi notevoli

O(a^N) - Costo esponenziale, spesso è troppo pesante da calcolare.

O(1) - Tempo costante.

Attenzione perché se il mio problema è piccolo non è detto che abbia bisogno dell'algoritmo più veloce
per N grande. Prendo in considerazione anche c.

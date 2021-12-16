# Codice

Viene eseguito passo passo proprio com'è salvato in memoria, tranne se non ho istruzioni di salto.

## Record di attivazione


## Indirizzo base

Indirizzo dove viene salvato il primo parametro.

Nel processore c'è un registro chiamato stack pointer che contiene la posizione corrente dello stack.

Il codice aggiuntivo inserito dal compilatore per realizzare la chiamata a funzione è detto *prologo*.
Il suo compito è quello di creare il record di attivazione, ad esempio.

[Function Entry - GCC Docs](https://gcc.gnu.org/onlinedocs/gccint/Function-Entry.html)

Il record di attivazione viene creato nello stack, struttura dati che funziono proprio come una pila.

Quando la funzione termina vado a fare il `pop` del RDA.

Dato il seguente snippet di codice, qual è la sequenza di attivazioni?

```c++
...
```

Sistema operativo --> main --> P --> Q --> R

Lo stack viene liberato in ordine inverso (R, Q, P...).

La sequenza dei collegamenti dinamici (delle chiamate a funzioni fatte) è detta **catena dinamica**.

Il codice che pulisce il RDA si chiama *epilogo*, che ha anche il compito di recuperare il valore
di ritorno della funzione.

## Spazio di indirizzamento di un processo

Il sistema operativo dà in gestione a un processo un'area di memoria che può usare liberamente, se però
va fuori dal suo orticello può venire terminato forzatamente.

Lo spazio libero nello spazio di indirizzamento di un processo può ridursi sia dal basso (cresce lo stack)
che dall'alto (cresce lo heap).


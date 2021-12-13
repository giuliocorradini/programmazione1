# I/O non formattato

Fino ad ora abbiamo usato gli operatori sugli stream (<< e >>) che trattano gli stessi come
sequenze di caratteri.

Lavorare con I/O non formattato significa lavorare più a basso livello come mera sequenza di byte.

Per gestire output non formattato usiamo delle **funzioni membro** degli oggetti cin e cout.

## Buffer

Un buffer è un array di byte utilizzato nelle operazioni di I/O.

Il *char* ha dimensione di esattamente 1 byte.

## Funzioni

### input (cin)

- `.get()` ritorna il valore del prossimo carattere presente nello stream. Se arrivo
alla fine del file viene restituita una costante EOF.

- `.get(c)` viene salvato nella reference (c) il prossimo carattere nello stream. Ma devo
passare una reference a intero.

- `.get(char *buffer, int n, char delimiter)` vengono letti al più di n byte entro il delimitatore
specificato. Viene aggiunto un '\0' alla fine nel buffer. Il delimitatore non viene rimosso, quindi
bisogna rimuoverlo manualmente con `.get()`

- `.peek()` controlla il prossimo byte del buffer. Se vedo che è EOF o \n non vado a chiamare .get, che
può causare errori nello stream se la riga è vuota.
In questo caso chiamerò un `.get()` a vuoto così consumo il '\n' e posso leggere la riga successiva

- `.read(char *buffer, int n)` legge n byte, li copia nell'array buffer

- `.gcount()` ritorna il numero di byte letti nell'ultima operazione.

### output (cout)

Un file che non è leggibile da un umano è detto file binario, che risulta più efficiente.
Per lavorare con i file binari si usa l'I/O non formattato.

Siccome il char è l'unità fondamentale, posso rappresentare qualsiasi sequenza di byte attraverso
un array di caratteri il cui indirizzo sarà un un `char *`.

Quindi se voglio salvare un double in modalità binaria su file, reinterpreto il double come
vettore di char.

```c++
reinterpret_cast<char *>(address);
```

Quindi per scrivere un array su file mi basta usare `.write`.

```c++
ofstream f("dst");
f.write(
    reinterpret_cast<char *>(a);
    sizeof(int) * 3
);
```

La scrittura non formattata risulta meno efficiente della formattata, visto che quest'ultima viene
bufferizzata.

### dereferenziazione

L'operatore `&` dereferenzia l'oggetto, ovvero ritorna il suo indirizzo in memoria.

## Accesso casuale

Quando accediamo ai byte dobbiamo sempre leggere sequenzialmente.

Si può fare anche l'accesso casuale andando a spostare il puntatore alla testa del file.

- `seekg(new_head)` per i file in ingresso (get)

- `seekp(new_head)` per i file di uscita (put)

Posso integrare le funzioni con `ios::beg` e `ios::end` che indicano l'offset dall'inizio e dalla
fine del file.

Se voglio sapere dove sono uso le funzioni:

- `tellg()` per i file di input

- `tellp()` per i file di output


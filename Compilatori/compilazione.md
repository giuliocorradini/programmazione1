# Compilazione

Supponiamo che esista qualcosa che esegua le operazioni e le istruzioni del linguaggio C.
Questo esecutore (vedi la slide sugli esecutori) possiamo supporlo una *macchina virtuale*
che capisce il concetto di variabile, e tutti gli altri costrutti del C.

La macchina fisica non capisce direttamente il C, infatti devo **compilare** il codice e
tradurlo in linguaggio maccina (il compilatore lo fa per me).

Il processore lavora con registri che possono cambiare in frazioni infinitesime di secondo,
più mi allontano dal processore meno veloci i transistor possono cambiare stato.

Come faccio ad avere come target tanti processori diversi della stessa famiglia? Compilo
per un sottoinsieme dell'instruction set compatibile con tutti i processori che mi servono.

Il C/C++ è un linguaggio di alto livello: si basano su un elaboratore che può processare istruzioni
non tipiche di un processore reale ma quelle del linguaggio.

Abbiamo chiamato questa caratteristica *macchina virtuale*.

## Traduzione sorgenti

Traduttore che traduce il codice sorgente nella sua rappresentazione in linguaggio macchina.

### Compilatori

Genera un eseguibile che dovrà essere mandato in esecuzione successivamente.

Riconosce e traduce.

### Interpreti

Traduce in tempo reale il codice sorgente e lo manda subito in esecuzione. Bash, Python sono
interpretati.

Riconosce e valuta.

Ogni linguaggio può essere in linea teorica compilato o interpretato, ma per loro natura ci sono delle
differenze. Java è particolare perché adotta un approccio ibrido.

Di solito un programma compilato viene eseguito più velocemente di uno interpretato (anche se il trend
negli ultimi anni si sta appiattendo).

## Fasi

Nel sorgente importo gli header delle librerie che contengono delle dichiarazioni. Il codice associato
agli identificatori contenuti nelle intestazioni è contenuto in file che contengo codice oggetto già
compilato.

Il linker (componente del compilatore) si occupa di "collegare" le funzioni di librerie esterne usate
con il codice oggetto delle librerie stesse.

A volte il compilatore non sa dove trovare le librerie che usiamo, quindi si passano i flag `-l` che
specificano quali vogliamo usare e dove si trovano.

`-lm` linka la libreria cmath.

### 1. Preprocessing

Genero un file sorgente modificato (valuto le direttive come `#define` etc.) che include anche le
dichirazioni importate.

### 2. Compiling

Viene generato il codice oggetto del codice che ho scritto.

### 3. Linking

Il codice che ho scritto viene collegato al codice delle librerie importate.

## Ambiente di programmazione

Insieme di linguaggi e strumenti in support alle varie fasi di sviluppo del codice.

Un ambiente può essere: Linux, bash, un editor e il compilatore (traduttore e linker).

Questi sono tutti programmi più o meno indipendenti, ne deriva che gli ambienti UNIX
sono ambienti di sviluppo.

Altrimenti posso anche usare degli IDE (ambienti di programmazione integrati). Sono più veloci da
usare ma gli ambienti non IDE permettono più scelta e sono migliori per la didattica.

#include <iostream>
#include <fstream>
using namespace std;

const char savefile[] = "memory.txt";

struct memblock_t {
    int start;
    int len;
    struct memblock_t *next;
};

struct memregion_t {
    int dim;
    struct memblock_t *chain;
};

/*
 * Create a memory block in dynamic memory, a block initialised as follow
 * (start:0, len:0) can be considered as the head of the chain.
 * In the program is used with this intent.
 */
memblock_t *memblock_new() {
    memblock_t *mb = new memblock_t;
    mb->start = 0;
    mb->len = 0;
    mb->next = nullptr;

    return mb;
}

void memblock_init(memblock_t &m, const int position, const int dimension) {
    m.start = position;
    m.len = dimension;
}


/*
 * Aggregate memblock_t functions: to treat memblock_t as a linked list
 */

void memchain_insert_after(memblock_t *prev, memblock_t *next) {
    memblock_t *after = prev->next;    //the remaining chain after prev
    prev->next = next;
    next->next = after;
}

void memchain_append(memblock_t *chain, memblock_t &next) {
    memblock_t *cursor = chain;
    while(cursor->next != nullptr) {    // go to the end
        cursor = cursor->next;
    }

    cursor->next = &next;
}

void memchain_free(memblock_t *chain) {

}

/*
 * Initialisez a new "static" (externally created) struct memregion_t
 * ideally a "default constructor"
 */
void memregion_new_static(memregion_t &r) {
    r.chain = memblock_new();
    r.dim = 0;
}

/*
 * Frees and resets previously used chain and sets maximum dimensions to n
 */
void memregion_init(memregion_t &r, const int n) {
    memchain_free(r.chain);
    r.chain = memblock_new();
    r.dim = n;
}

void stampa_memoria(memregion_t &r) {
    //Print numbers
    for(int i=0; i<r.dim; i++)
        cout << i % 10;
    cout << endl;

    //Print allocated cells
    int k = 0;
    memblock_t *cursor = r.chain;
    while((cursor = cursor->next)) {
        if(k < cursor->start)
            for(int i=k; i<cursor->start; i++) cout << '-';

        for(int i=0; i<cursor->len; i++) cout << '*';

        k = cursor->start + cursor->len;
    }

    if(k != r.dim)
        for(int i=k; i<r.dim; i++) cout << '-';    //fill remaining empty spaces

    cout << endl;
    
/* debug print
    memblock_t *c = r.chain;
    do {
        cout << "start: " << c->start << ", len: " << c->len << ", has next: " << (c->next != nullptr) << endl;
    } while((c = c->next));
    */
}

/*
 *  (alias of)alloca_oggetto
 *
 * allocates a new memory block of specified size at specified position
 * @return true if allocation was successful, false otherwise
 */
bool memregion_alloc(memregion_t &r, const int position, const int size) {

    /* control free memory before previously allocated blocks */
    int k = 0;  //free memory controlled up until k, k to be controlled

    memblock_t *c = r.chain;    //chain cursor
    memblock_t *prev = r.chain;

    while((c = c->next)) {
        k = c->start + c->len;

        if(position < k) {
            if(position + size <= c->start) {
                memblock_t *new_mb = memblock_new();
                memblock_init(*new_mb, position, size);
                memchain_insert_after(prev, new_mb);
                return true;
            } else {
                break;
            }
        }

        prev = c;
    }

    //control final free memory if free space wasn't found before
    if(position >= k && position + size <= r.dim) {
        memblock_t *new_mb = memblock_new();
        new_mb->start = position;
        new_mb->len = size;
        memchain_insert_after(prev, new_mb);
        return true;
    }

    return false;
}

bool memregion_alloc_move(memregion_t &r, const int position, const int size) {

    int k = 0;

    memblock_t *c = r.chain;    //chain cursor
    memblock_t *prev = r.chain;

    memblock_t pre_head_dummy = {.start=0, .len=0, .next=r.chain};  //pointer to head
    memblock_t *prev_prev = &pre_head_dummy;

    while((c = c->next)) {
        k = c->start + c->len;

        if(position < k) {
            if(position + size <= c->start) {
                memblock_t *new_mb = memblock_new();
                memblock_init(*new_mb, position, size);
                memchain_insert_after(prev, new_mb);
                return true;
            } else if(position + size <= c->next->start - c->len) {    //idealmente riempio lo spazio vuoto tutto a destra, prendendo l'inizio del successivo meno la lunghezza di questo
                memblock_t *new_mb = memblock_new();
                memblock_init(*new_mb, position, size);

                c->start = (c->next->start - c->len);   //the offset
                memchain_insert_after(prev, new_mb);
                return true;
            } else {
                break;
            }
        }

        prev_prev = prev;
        prev = c;
    }

    //control final free memory if free space wasn't found before
    if(position >= k && position + size <= r.dim) {
        memblock_t *new_mb = memblock_new();
        memblock_init(*new_mb, position, size);
        memchain_insert_after(prev, new_mb);
        return true;
    }

    return false;
}

bool serialize_memory(const memregion_t &r) {
    ofstream f(savefile);

    if(!f)
        return false;

    memblock_t *c = r.chain;

    f << r.dim << endl;
    do {
        f << c->start << ' ' << c->len << endl;
    } while((c = c->next));

    return static_cast<bool>(f);
}

bool deserialize_memory(memregion_t &r) {
    ifstream f(savefile);

    if(!f)
        return false;

    int chain_dimension;
    f >> chain_dimension;

    memregion_init(r, chain_dimension);

    bool parsing_status = true;

    int start, len;
    while(f >> start >> len)
        parsing_status &= memregion_alloc(r, start, len);

    return f.eof() && !f.bad() && parsing_status;
}

int main() {
    const char menu[] =
        "1. Reinizializza memoria\n"
        "2. Stampa memoria\n"
        "3. Alloca oggetto\n"
        "4. Salva memoria\n"
        "5. Carica memoria\n"
        "6. Alloca oggetto 2\n"
        "7. Esci\n";

    memregion_t region;
    memregion_new_static(region);

    // Variabili di appoggio
    int pool_dim, posizione, dimensione;

    while (true) {
        cout<<menu<<endl;
        int scelta;
        cin>>scelta;

        cout<<endl; // per il corretto funzionamento del tester

        switch (scelta) {
        case 1:
            cout << "dimensione del pool: ";
            cin >> pool_dim;

            memregion_init(region, pool_dim);
            break;
        case 2:
            stampa_memoria(region);
            break;
        case 3:
            cout << "posizione: ";
            cin >> posizione;

            cout << "dimensione: ";
            cin >> dimensione;

            if(memregion_alloc(region, posizione, dimensione))
                cout << "oggetto allocato" << endl;
            else
                cout << "non ho memoria libera nello spazio richiesto" << endl;
            break;
        case 4:
            if(serialize_memory(region))
                cout << "Salvataggio avvenuto correttamente" << endl;
            else
                cout << "Errore nel salvataggio" << endl;
            break;
        case 5:
            if(deserialize_memory(region))
                cout << "Caricamento avvenuto correttamente" << endl;
            else
                cout << "Errore durante il caricamento" << endl;
            break;
        case 6:
            cout << "posizione: ";
            cin >> posizione;

            cout << "dimensione: ";
            cin >> dimensione;

            if(memregion_alloc_move(region, posizione, dimensione))
                cout << "oggetto allocato" << endl;
            else
                cout << "non ho memoria libera nello spazio richiesto" << endl;
            break;
        case 7:
            return 0;
        default:
            cout<<"Scelta errata"<<endl;
        }
    }

    return 1;
}

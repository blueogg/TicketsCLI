#ifndef LISTAPASSEGGERI_H
#define LISTAPASSEGGERI_H
#include "./passeggeri.h"

typedef struct node {
    passeggero _passeggero;
    struct node* next;
} node;

node* initListaPasseggeri(int numeroPasseggeri);
void aggiungiNodi(node** head, int numeroNodi);

#endif

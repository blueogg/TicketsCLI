#ifndef LISTAPASSEGGERI_H
#define LISTAPASSEGGERI_H
#include "./passeggeri.h"
/**
 * @file listaPasseggeri.h
 * @brief Gestione liste concatenate di passeggeri
 */

/**
 * @brief Nodo della lista passeggeri
 */
typedef struct node {
    passeggero _passeggero;
    struct node* next;
} node;

/**
 * @brief Inizializza una lista di passeggeri
 * @param numeroPasseggeri Numero di passeggeri da aggiungere
 * @return Puntatore alla testa della lista
 */
node* initListaPasseggeri(int numeroPasseggeri);
/**
 * @brief Aggiunge nodi a una lista esistente
 * @param head Puntatore al puntatore della testa
 * @param numeroNodi Numero di nodi da aggiungere
 */
void aggiungiNodi(node** head, int numeroNodi);

#endif

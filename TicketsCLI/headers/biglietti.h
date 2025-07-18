#ifndef BIGLIETTI_H
#define BIGLIETTI_H
#include "./passeggeri.h"
#include "./costanti.h"


typedef struct {
    char luogo[lunghezza_luogo];
    char data[lunghezza_data];
    char ora[lunghezza_ora];
} rotta;

// Strutture biglietto
typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    passeggero utente;
} bigliettoPasseggero;

typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    int lunghezza_auto;
    struct node* head;
} bigliettoMacchina;

//STRUTTURA ROTTA



// Funzioni
void creaBigliettoPasseggero();
void creaBigliettoMacchina();
int contaBigliettiPasseggero();
int contaBigliettiMacchina();
int contaBigliettiTotali();
int guadagnoTotale();
int guadagnoPerGiorno();

#endif

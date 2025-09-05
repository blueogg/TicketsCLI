#ifndef BIGLIETTI_H
#define BIGLIETTI_H
#include "./passeggeri.h"
#include "./costanti.h"
/**
 * @file biglietti.h
 * @brief Definizioni e operazioni sui biglietti
 */


/**
 * @brief Struttura dati rotta
 */
typedef struct {
    char luogo[lunghezza_luogo];
    char data[lunghezza_data];
    char ora[lunghezza_ora];
} rotta;

// Strutture biglietto
/**
 * @brief Biglietto per passeggero singolo
 */
typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    passeggero utente;
} bigliettoPasseggero;
/**
 * @brief Biglietto per auto
 */
typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    int lunghezza_auto;
    struct node* head;
} bigliettoMacchina;

//STRUTTURA ROTTA



// Funzioni
/**
 * @brief Crea un nuovo biglietto per passeggero singolo
 */
void creaBigliettoPasseggero();
/**
 * @brief Crea un nuovo biglietto per veicolo con passeggeri multipli
 */
void creaBigliettoMacchina();
/**
 * @brief Conta i biglietti passeggeri singoli esistenti
 * @return Numero di biglietti passeggeri
 */
int contaBigliettiPasseggero();
/**
 * @brief Conta i biglietti veicolo esistenti
 * @return Numero di biglietti veicolo
 */
int contaBigliettiMacchina();
/**
 * @brief Conta tutti i biglietti esistenti
 * @return Somma di biglietti passeggeri e veicoli
 */
int contaBigliettiTotali();
/**
 * @brief Calcola il guadagno totale
 * @return Guadagno complessivo dell'agenzia
 */
int guadagnoTotale();
/**
 * @brief Calcola il guadagno per un giorno specifico
 * @return Guadagno del giorno selezionato
 */
int guadagnoPerGiorno();

#endif

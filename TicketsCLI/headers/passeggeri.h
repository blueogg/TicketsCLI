#ifndef PASSEGGERI_H
#define PASSEGGERI_H
#include "./costanti.h"
/**
 * @file passeggeri.h
 * @brief Definizioni e operazioni sui passeggeri
 */

 /**
 * @brief Struttura dati passeggero
 */
typedef struct {
    char nome[lunghezza_nome];
    char cognome[lunghezza_cognome];
} passeggero;

/**
 * @brief Stampa l'elenco dei passeggeri singoli
 */
void nomiBigliettiPasseggero();
/**
 * @brief Stampa l'elenco dei passeggeri in auto
 */
void nomiBigliettiMacchina();
/**
 * @brief Filtra passeggeri per luogo di partenza
 * @param luogo Luogo di partenza da filtrare
 */
void passeggeriPerLuogoPartenza();
/**
 * @brief Filtra passeggeri per luogo di arrivo
 * @param luogo Luogo di arrivo da filtrare
 */
void passeggeriPerLuogoArrivo();

#endif

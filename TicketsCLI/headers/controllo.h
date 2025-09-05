#ifndef CONTROLLO_H
#define CONTROLLO_H
    #include "./costanti.h"
    #include "./passeggeri.h"

    /**
 * @file controllo.h
 * @brief Funzioni di validazione input
 */

 /**
 * @brief Pulisce il buffer di input
 */
void controlloBuffer();
/**
 * @brief Valida nome e cognome passeggero
 * @param _passeggero Struttura da validare
 */
void controlloNome(passeggero _passeggero);
/**
 * @brief Valida sintassi di luogo/data/ora
 * @param luogo Stringa luogo (solo lettere)
 * @param data Data in formato dd-mm-yyyy
 * @param ora Ora in formato hh-mm
 */
void controlloDatiSintattico(char luogo[lunghezza_luogo], char data[lunghezza_data], char ora[lunghezza_ora]);
/**
 * @brief Verifica la coerenza semantica tra due date
 * @param data1 Data di partenza (dd-mm-yyyy)
 * @param data2 Data di arrivo (dd-mm-yyyy)
 * @post Verifica che la differenza non superi 2 giorni
 */

void controlloDataSemantico(char data1[lunghezza_data], char data2[lunghezza_data]);
/**
 * @brief Versione thread-safe di strtok
 * @param str Stringa da tokenizzare
 * @param delim Delimitatori
 * @param nextp Puntatore allo stato interno
 * @return Token corrente o NULL
 */
char* strtok_r(char *str, const char *delim, char **nextp); // (NON PRESENTE IN MINGW, COMPATIBILITA')

#endif

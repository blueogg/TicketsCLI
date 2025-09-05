#include <stdio.h>
#include "../headers/filemanager.h"

/**
 * @file filemanager.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

// RESTITUISCE PUNTATORE AL FILE DEI BIGLIETTI DI TIPO PASSEGGERO
/**
 * @pre _ACCESS tra 1 (READ) e 3 (READ)
 * @post Restituisce ticketsPassengers o NULL se errore
 */
FILE* ticketsPassenger(ACCESS _ACCESS) {
    FILE* fPtr = NULL;
    switch(_ACCESS) {
        case 1: fPtr = fopen("data/ticketsPassengers.bin", "r"); return fPtr; break;
        case 2: fPtr = fopen("data/ticketsPassengers.bin", "ab"); break;
        case 3: fPtr = fopen("data/ticketsPassengers.bin", "ab+"); return fPtr; break;
    }
    return fPtr;
}

// RESTITUISCE PUNTATORE AL FILE DEI BIGLIETTI DI TIPO MACCHINA
/**
 * @pre _ACCESS tra 1 (READ) e 4 (RB+)
 * @post Restituisce ticketsCar aperto in modalità binaria
 */
FILE* ticketsCar(ACCESS _ACCESS) {
    FILE* fPtr = NULL;
    switch(_ACCESS) {
        case 1: fPtr = fopen("data/ticketsCar.bin", "r"); return fPtr; break;
        case 2: fPtr = fopen("data/ticketsCar.bin", "ab"); break;
        case 3: fPtr = fopen("data/ticketsCar.bin", "ab+"); return fPtr; break;
        case 4: fPtr = fopen("data/ticketsCar.bin", "rb+"); return fPtr; break;
    }
    return fPtr;
}

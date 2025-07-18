#include <stdio.h>
#include "../headers/filemanager.h"

// Apre il file dei biglietti passeggeri in base alla modalità di accesso
FILE* ticketsPassenger(ACCESS _ACCESS) {
    FILE* fPtr = NULL;
    switch(_ACCESS) {
        case 1: fPtr = fopen("data/ticketsPassengers.bin", "r"); return fPtr; break;
        case 2: fPtr = fopen("data/ticketsPassengers.bin", "ab"); break;
        case 3: fPtr = fopen("data/ticketsPassengers.bin", "ab+"); return fPtr; break;
    }
    return fPtr;
}

// Apre il file dei biglietti auto in base alla modalità di accesso
FILE* ticketsCar(ACCESS _ACCESS) {
    FILE* fPtr = NULL;
    switch(_ACCESS) {
        case 1: fPtr = fopen("data/ticketsCar.bin", "r"); return fPtr; break;
        case 2: fPtr = fopen("data/ticketsCar.bin", "ab"); break;
        case 3: fPtr = fopen("data/ticketsCar.bin", "ab+"); return fPtr; break;
    }
    return fPtr;
}

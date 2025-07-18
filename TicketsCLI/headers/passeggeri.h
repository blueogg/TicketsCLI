#ifndef PASSEGGERI_H
#define PASSEGGERI_H
#include "./costanti.h"

typedef struct {
    char nome[lunghezza_nome];
    char cognome[lunghezza_cognome];
} passeggero;

void nomiBigliettiPasseggero();
void nomiBigliettiMacchina();
void passeggeriPerLuogoPartenza();
void passeggeriPerLuogoArrivo();

#endif

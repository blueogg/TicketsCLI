#include <stdio.h>
#include "../headers/passeggeri.h"
#include "../headers/biglietti.h"
#include "../headers/filemanager.h"
/**
 * @file passeggeri.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

// STAMPA LISTA COMPLETA DEGLI UTENTI DI TIPO PASSEGGERO
/**
 * @pre File ticketsPassengers.bin esistente e leggibile
 * @post Stampa lista passeggeri o messaggio "Nessun biglietto trovato"
 */
void nomiBigliettiPasseggero() {
    bigliettoPasseggero biglietto;
    FILE* fPtr = ticketsPassenger(READ);
    int numeroBigliettiPasseggero = contaBigliettiPasseggero();
    if(fPtr != NULL) {
        if(numeroBigliettiPasseggero != 0) {
            printf("\n%s\n", "Lista dei nomi biglietti passeggero:");
            for(int i = 0; i < numeroBigliettiPasseggero; i++) {
                fread(&biglietto, sizeof(biglietto), 1, fPtr);
                printf("%s%i: %s %s\n", "Utente ", i+1, biglietto.utente.nome, biglietto.utente.cognome);
            }
            fclose(fPtr);
        } else { puts("Nessun biglietto trovato"); }
    }
    menu();
}

//STAMPA LISTA COMPLETA DEGLI UTENTI DI TIPO MACCHINA
/**
 * @pre File ticketsCar.bin esistente e leggibile
 * @post Stampa lista passeggeri auto con formato "Utente N: Nome Cognome"
 */
void nomiBigliettiMacchina(){

FILE* fPtr = ticketsCar(READ);
bigliettoMacchina biglietto;
passeggero _passeggero;
int temp;
int numeroBigliettiMacchina = contaBigliettiMacchina();

if(fPtr != NULL){
    printf("\n%s\n", "Lista dei nomi biglietti macchina:");
    for(int i = 0; i < numeroBigliettiMacchina; i++){

        fread(&temp, sizeof(int), 1, fPtr);
        fseek(fPtr, sizeof(rotta) * 2 + sizeof(int) *2, SEEK_CUR);
        for(int j = 0; j < temp; j++){
        fread(&_passeggero, sizeof(passeggero), 1, fPtr);
        printf("%s%i: %s %s\n", "Utente ", j+1, _passeggero.nome, _passeggero.cognome);
        }


    }




}






}

//STAMPA LISTA DEI PASSEGGERI DATO UN LUOGO DI PARTENZA
/**
 * @pre Luogo partenza inserito da stdin (max 30 caratteri)
 * @post Stampa passeggeri filtrati per luogo (case-insensitive)
 */
void passeggeriPerLuogoPartenza() {
    passeggero _passeggero;
    rotta partenza;
    bigliettoMacchina _bigliettoMacchina;
    bigliettoPasseggero _bigliettoPasseggero;
    printf("\n%s\n", "Inserisci luogo di partenza per cui elencare i passeggeri:");
    scanf("%30s", partenza.luogo);
    printf("\n%s\n", "Lista passeggeri per il luogo di partenza selezionato: ");
    puts("Passeggeri biglietto singolo");
    int check;
    FILE* fPtr1 = ticketsPassenger(READ);
    while(fread(&_bigliettoPasseggero, sizeof(bigliettoPasseggero), 1, fPtr1) == 1) {
        check = 0;
        for(int i = 0; i<lunghezza_luogo; i++) {
            if(partenza.luogo[i] != '\0') {
                if(tolower(partenza.luogo[i]) == tolower(_bigliettoPasseggero.partenza.luogo[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { }
        else { printf("\n%s\t%s\t%s\n", _bigliettoPasseggero.utente.nome, _bigliettoPasseggero.utente.cognome, _bigliettoPasseggero.partenza.data); }
    }
    fclose(fPtr1);
    printf("\n%s\n", "Passeggeri biglietto macchina");
    int num = 0;
    FILE* fPtr2 = ticketsCar(READ);
    while(fread(&num, sizeof(int),1, fPtr2) == 1) {
        fread(&_bigliettoMacchina.partenza, sizeof(rotta), 1, fPtr2);
        check = 0;
        for(int i = 0; i<lunghezza_luogo; i++) {
            if(partenza.luogo[i] != '\0') {
                if(tolower(partenza.luogo[i]) == tolower(_bigliettoMacchina.partenza.luogo[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { }
        else {
            fseek(fPtr2, sizeof(rotta) + sizeof(int) * 2, SEEK_CUR);
            for(int i = 0; i < num; i++) {
                fread(&_passeggero, sizeof(passeggero), 1, fPtr2);
                printf("\n%s\t%s\t%s\n", _passeggero.nome, _passeggero.cognome, _bigliettoMacchina.partenza.data);
            }
        }
    }
    fclose(fPtr2);
}

//STAMPA LISTA DEI PASSEGGERI DATO UN LUOGO DI ARRIVO
/**
 * @pre Luogo arrivo inserito da stdin (max 30 caratteri)
 * @post Stampa passeggeri filtrati per luogo arrivo (case-insensitive)
 */
void passeggeriPerLuogoArrivo(){
passeggero _passeggero;
    rotta arrivo;
    bigliettoMacchina _bigliettoMacchina;
    bigliettoPasseggero _bigliettoPasseggero;
    printf("\n%s\n", "Inserisci luogo di arrivo per cui elencare i passeggeri:");
    scanf("%30s", arrivo.luogo);
    printf("\n%s\n", "Lista passeggeri per il luogo di arrivo selezionato: ");
    puts("Passeggeri biglietto singolo");
    int check;
    FILE* fPtr1 = ticketsPassenger(READ);
    while(fread(&_bigliettoPasseggero, sizeof(bigliettoPasseggero), 1, fPtr1) == 1) {
        check = 0;
        for(int i = 0; i<lunghezza_luogo; i++) {
            if(_bigliettoPasseggero.arrivo.luogo[i] != '\0') {
                if(tolower(arrivo.luogo[i]) == tolower(_bigliettoPasseggero.arrivo.luogo[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { }
        else { printf("\n%s\t%s\t%s\n", _bigliettoPasseggero.utente.nome, _bigliettoPasseggero.utente.cognome, _bigliettoPasseggero.arrivo.data); }
    }
    fclose(fPtr1);
    printf("\n%s\n", "Passeggeri biglietto macchina");
    int num = 0;
    FILE* fPtr2 = ticketsCar(READ);
    while(fread(&num, sizeof(int),1, fPtr2) == 1) {
        fseek(fPtr2, sizeof(rotta), SEEK_CUR);
        fread(&_bigliettoMacchina.arrivo.luogo, sizeof(rotta), 1, fPtr2);
        check = 0;
        for(int i = 0; i<lunghezza_luogo; i++) {
            if(_bigliettoMacchina.arrivo.luogo[i] != '\0') {
                if(tolower(arrivo.luogo[i]) == tolower(_bigliettoMacchina.arrivo.luogo[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { fseek(fPtr2, sizeof(int) * 2 + sizeof(passeggero) * num, SEEK_CUR); }
        else {

            fseek(fPtr2, sizeof(int) * 2, SEEK_CUR);
            for(int i = 0; i < num; i++) {
               fread(&_passeggero, sizeof(passeggero), 1, fPtr2);
               printf("\n%s\t%s\t%s\n", _passeggero.nome, _passeggero.cognome, _bigliettoMacchina.arrivo.data);
            }

            }
        }
            fclose(fPtr2);
    }

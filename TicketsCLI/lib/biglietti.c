#include <stdio.h>
#include "../headers/filemanager.h"
#include "../headers/biglietti.h"
#include "../headers/controllo.h"
#include "../headers/listaPasseggeri.h"
/**
 * @file biglietti.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

// CREA UN NUOVO BIGLIETTO DI TIPO PASSEGGERO
/**
 * @pre Input utente valido (scanf completati)
 * @post Scrive biglietto passeggero su ticketsPassengers o errore su stdout
 */
void creaBigliettoPasseggero() {
    bigliettoPasseggero biglietto;
    passeggero _passeggero;
    rotta partenza;
    rotta arrivo;
    printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
    scanf("%15s%15s", _passeggero.nome, _passeggero.cognome);
    controlloBuffer();
    controlloNome(_passeggero);
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%30s%11s%6s", partenza.luogo, partenza.data, partenza.ora);
    controlloBuffer();
    controlloDatiSintattico(partenza.luogo, partenza.data, partenza.ora);
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy)e ora(hh-mm) dell'arrivo");
    scanf("%30s%11s%6s", arrivo.luogo, arrivo.data, arrivo.ora);
    controlloBuffer();
    controlloDatiSintattico(arrivo.luogo, arrivo.data, arrivo.ora);
    controlloDataSemantico(partenza.data, arrivo.data);
    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 15;
    biglietto.utente = _passeggero;
    int check = 0;
    FILE* fPtr = ticketsPassenger(WRITE);
    if(fPtr != NULL) {
        check = fwrite(&biglietto, sizeof(biglietto), 1, fPtr);
        if(check != 0) { puts("Biglietto creato correttamente"); }
        else { puts("Errore nella creazione del biglietto"); }
        fclose(fPtr);
        menu();
    } else { puts("Impossibile aprire il file"); menu(); }
}

// CREA UN NUOVO BIGLIETTO DI TIPO MACCHINA
/**
 * @pre Input utente valido, lista passeggeri inizializzata
 * @post Scrive biglietto auto su ticketsCar
 */
void creaBigliettoMacchina() {
    int numeroPasseggeri;
    int dimensioniAuto;
    node* head;
    bigliettoMacchina biglietto;
    rotta partenza;
    rotta arrivo;
    printf("%s\n", "Quanti passeggeri nell'auto?");
    scanf("%i", &numeroPasseggeri);
    head = initListaPasseggeri(numeroPasseggeri);
    node* temporaneo = head;
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%30s%11s%6s", partenza.luogo, partenza.data,partenza.ora);
    controlloBuffer();
    controlloDatiSintattico(partenza.luogo, partenza.data, partenza.ora);
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy)e ora(hh-mm) dell'arrivo");
    scanf("%30s%11s%6s", arrivo.luogo, arrivo.data, arrivo.ora);
    controlloBuffer();
    controlloDatiSintattico(arrivo.luogo, arrivo.data, arrivo.ora);
    controlloDataSemantico(partenza.data, arrivo.data);
    printf("\n%s\n", "Inserisci dimensioni auto (m)");
    scanf("%i", &dimensioniAuto);
    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 15 * numeroPasseggeri + 5;
    biglietto.lunghezza_auto = dimensioniAuto;
    biglietto.head = head;
    FILE* fPtr = ticketsCar(WRITE);
    if(fPtr != NULL) {
        fwrite(&numeroPasseggeri, sizeof(int), 1, fPtr);
        fwrite(&(biglietto.partenza), sizeof(rotta), 1, fPtr);
        fwrite(&(biglietto.arrivo), sizeof(rotta), 1, fPtr);
        fwrite(&(biglietto.prezzo), sizeof(int), 1, fPtr);
        fwrite(&(biglietto.lunghezza_auto), sizeof(int), 1, fPtr);
        if(temporaneo != NULL) {
            while (temporaneo) {
                fwrite(&(temporaneo->_passeggero), sizeof(passeggero), 1, fPtr);
                temporaneo = temporaneo->next;
            }
        printf("%s\n", "Biglietto creato correttamente");
            fclose(fPtr);
            menu();
        }
    } else { puts("Impossibile aprire il file"); menu(); }
}

// RESTITUISCE IL NUMERO TOTALE DI BIGLIETTI
/**
 * @pre File ticketsPassengers.bin e ticketsCar.bin esistenti
 * @post Restituisce conteggio totale biglietti
 */
int contaBigliettiTotali() { return contaBigliettiPasseggero() + contaBigliettiMacchina(); }

// RESTITUISCE IL NUMERO DI BIGLIETTI DI TIPO PASSEGGERO

/**
 * @pre File ticketsPassengers.bin esistente
 * @post Restituisce numero biglietti passeggeri
 */
int contaBigliettiPasseggero() {
    int contatore = 0;
    bigliettoPasseggero biglietto;
    FILE* fPtr = ticketsPassenger(READ);
    if(fPtr != NULL) {
        while(fread(&biglietto, sizeof(biglietto), 1, fPtr)) { contatore++; }
        fclose(fPtr);
    } else { puts("Impossibile aprire il file"); }
    return contatore;
}

// RESTITUISCE IL NUMERO DI BIGLIETTI DI TIPO MACCHINA
/**
 * @pre File ticketsCar.bin esistente
 * @post Restituisce numero biglietti auto
 */
int contaBigliettiMacchina() {
    int temporaneo;
    int contatore = 0;
    FILE* fPtr = ticketsCar(READ);
    if(fPtr != NULL) {
        while(fread(&temporaneo, sizeof(int), 1, fPtr) == 1) {
            contatore++;
            fseek(fPtr, sizeof(rotta) * 2 + sizeof(int) * 2 + sizeof(passeggero) * temporaneo, SEEK_CUR);
        }
    } else { puts("Errore nell'apertura del file"); menu(); }
    return contatore;
}

//RESTITUISCE IL GUADAGNO PER UN DETERMINATO GIORNO
/**
 * @pre Data inserita nel formato dd-mm-yyyy
 * @post Restituisce guadagno per la data specificata
 */
int guadagnoPerGiorno() {
    int totale = 0;
    rotta partenza;
    bigliettoMacchina _bigliettoMacchina;
    bigliettoPasseggero _bigliettoPasseggero;
    printf("\n%s\n", "Inserisci data per cui calcolare il guadagno:");
    scanf("%11s", partenza.data);
    int check = 0;
    int valore = 0;
    FILE* fPtr1 = ticketsPassenger(READ);
    while(fread(&_bigliettoPasseggero, sizeof(bigliettoPasseggero), 1, fPtr1) == 1) {
        check = 0;
        for(int i = 0; i<lunghezza_data; i++) {
            if(_bigliettoPasseggero.partenza.data[i] != '\0') {
                if(tolower(partenza.data[i]) == tolower(_bigliettoPasseggero.partenza.data[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { }
        else { valore = _bigliettoPasseggero.prezzo; totale += valore; }
    }
    fclose(fPtr1);
    int num = 0;
    FILE* fPtr2 = ticketsCar(READ);
    while(fread(&num, sizeof(int),1, fPtr2) == 1) {
        fread(&_bigliettoMacchina.partenza, sizeof(rotta), 1, fPtr2);
        check = 0;
        for(int i = 0; i<lunghezza_data; i++) {
            if(_bigliettoMacchina.partenza.data[i] != '\0') {
                if(tolower(partenza.data[i]) == tolower(_bigliettoMacchina.partenza.data[i])) { }
                else { check = 1; }
            } else { break; }
        }
        if(check == 1) { }
        else {
            fseek(fPtr2, sizeof(rotta), SEEK_CUR);
            fread(&valore, sizeof(int), 1, fPtr2);
            totale += valore;
            fseek(fPtr2, sizeof(int) + sizeof(passeggero) * num, SEEK_CUR);
        }
    }
    fclose(fPtr2);
    return totale;
}

//RESTITUISCE IL GUADAGNO PER UN DETERMINATO GIORNO

/**
 * @pre File dei biglietti esistenti
 * @post Restituisce guadagno totale
 */
int guadagnoTotale() {
    int totale = 0;
    int valore = 0;
    int temp = 0;
    FILE* fPtr = ticketsCar(READ);
    if(fPtr != NULL) {
        while(fread(&temp, sizeof(int),1, fPtr) == 1) {
            fseek(fPtr, sizeof(rotta) * 2, SEEK_CUR);
            fread(&valore, sizeof(int), 1, fPtr);
            totale += valore;
            fseek(fPtr, sizeof(int) + sizeof(passeggero) * temp, SEEK_CUR);
        }
        return totale + 15 * contaBigliettiPasseggero();
    } else { puts("Errore nell'apertura del file"); }
}

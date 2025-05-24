#include <stdio.h>
#include "../headers/tickets.h"
//In questo file definiamo l'implementazione delle funzioni.

FILE* ticketsPassenger(ACCESS _ACCESS){
FILE* fPtr = NULL;
switch(_ACCESS){
case 1:
    fPtr = fopen("data/ticketsPassengers.bin", "r");
    return fPtr;
    break;
case 2:
    fPtr = fopen("data/ticketsPassengers.bin", "ab");
    break;
case 3:
    fPtr = fopen("data/ticketsPassengers.bin", "ab+");
    return fPtr;
    break;
}
return fPtr;
}

void menu(){
    printf("\n%s:\n\n%s\n%s\n\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto passeggero", "2 - Conta numero dei biglietti");
    while(1){
    switch(getchar()){
    case '1':
        creaBigliettoPasseggero();
        break;
    case '2':
        nomiBigliettiPasseggero();
        break;
    }
    }
}

void creaBigliettoPasseggero(){

    bigliettoPasseggero biglietto;
    passeggero _passeggero;
    rotta partenza;
    rotta arrivo;

//INPUT
    printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
    scanf("%s%s", _passeggero.nome, _passeggero.cognome);
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%s%s%s", partenza.luogo, partenza.data, partenza.ora);
    printf("\n%s:\n", "Inserisci luogo, dataa (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf("%s%s%s", arrivo.luogo, arrivo.data, arrivo.ora);

//BIGLIETTO

    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 5;
    biglietto.utente = _passeggero;

//SCRITTURA BIGLIETTO SU FILE
    int check = 0;
    FILE* fPtr = ticketsPassenger(WRITE);
    if(fPtr != NULL){
    check = fwrite(&biglietto, sizeof(biglietto), 1, fPtr);
    if(check != 0){
    puts("Biglietto creato correttamente");
    }else { puts("Errore nella creazione del biglietto"); }
    fclose(fPtr);
    menu();
    }
    else {
        puts("Impossibile aprire il file");
        menu();
    }
}

int contaBigliettiTotali(){

int a = contaBigliettiPasseggero();
int b = 0; // Biglietti macchina ancora da creare
return a+b;
}

int contaBigliettiPasseggero(){
int count = 0;
bigliettoPasseggero biglietto;
    FILE* fPass = ticketsPassenger(READ);
    if(fPass != NULL){
    while(fread(&biglietto, sizeof(biglietto), 1, fPass)){
        count++;
    }
    }else { puts("Impossibile aprire il file"); }
    fclose(fPass);
    return count;
}

void nomiBigliettiPasseggero(){
    bigliettoPasseggero biglietto;
    FILE* fPass = ticketsPassenger(READ);
    int a = contaBigliettiPasseggero();
    if(fPass != NULL){
        if(a != 0){

        printf("\n%s\n", "Lista dei nomi biglietti passeggero:");
        for(int i = 0; i < a; i++)
            {
        fread(&biglietto, sizeof(biglietto), 1, fPass);
        printf("%s%i: %s %s\n", "Utente", i+1, biglietto.utente.nome, biglietto.utente.cognome);
            }
        } else {puts("Nessun biglietto trovato");}

    }
    menu();
}

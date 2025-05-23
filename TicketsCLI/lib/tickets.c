#include <stdio.h>
#include "../headers/tickets.h"
//In questo file definiamo l'implementazione delle funzioni.


void menu(){
    puts("");
    printf("%s:\n\n%s\n%s\n\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto passeggero", "2 - Conta numero dei biglietti");
    while(1){
    switch(getchar()){
    case '1':
        creaBigliettoPasseggero();
        break;
    case '2':
        contaBiglietti();
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
    puts("");
    printf("%s: \n", "Inserisci nome e cognome del passeggero");
    scanf("%s%s", _passeggero.nome, _passeggero.cognome);
    puts("");
    printf("%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%s%s%s", partenza.luogo, partenza.data, partenza.ora);
    printf("%s:\n", "Inserisci luogo, dataa (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf("%s%s%s", arrivo.luogo, arrivo.data, arrivo.ora);

//BIGLIETTO

    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 5;
    biglietto.utente = _passeggero;

//SCRITTURA BIGLIETTO SU FILE

    FILE* fPtr = NULL;
    fPtr = fopen("data/ticketsPassengers.bin", "ab+"); // Niente fPtr == NULL check perchè ab+ non ritorna mai NULL (crea il file se non esiste)
    if(fPtr != NULL){
    fwrite(&biglietto, sizeof(biglietto), 1, fPtr);
    puts("Biglietto creato correttamente");
    fclose(fPtr);
    menu();
    }
    else {
        puts("Operazione fallita");
        puts("");
        menu();
    }
}

int contaBiglietti(){

int a = numeroBigliettiPasseggero();
int b = 0; // Biglietti macchina ancora da creare
numeroBiglietti = a + b;
printf("Numero totale dei biglietti: %i", numeroBiglietti);
menu();
}

int numeroBigliettiPasseggero(){

int count = 0;
bigliettoPasseggero biglietto;

    FILE* fPass; // biglietti passeggeri
    fPass = fopen("data/ticketsPassengers.bin", "r+"); // Biglietti macchin
    while(fread(&biglietto, sizeof(biglietto), 1, fPass) != NULL ){
        count++;
    }
    return count;

}

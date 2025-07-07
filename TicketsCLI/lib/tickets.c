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

FILE* ticketsCar(ACCESS _ACCESS){

FILE* fPtr = NULL;
switch(_ACCESS){
case 1:
    fPtr = fopen("data/ticketsCar.bin", "r");
    return fPtr;
    break;
case 2:
    fPtr = fopen("data/ticketsCar.bin", "ab");
    break;
case 3:
    fPtr = fopen("data/ticketsCar.bin", "ab+");
    return fPtr;
    break;
}
return fPtr;

}

void controlloBuffer(){
int a = 0;
int b;
while ((b = getchar()) != '\n' && b != EOF) {
    a = 1;
}
if (a) {
    puts("Input troppo lungo. Operazione annullata");
    menu();
}
}

void menu(){
    while(1){
    printf("\n\n%s:\n\n%s\n%s\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto Passeggero Singolo", "2 - Crea biglietto passeggeri multipli con macchina");
    printf("%s\n%s\n\%s\n\n", "3 - Conta Biglietti totali", "4 - Elenco passeggeri per luogo di partenza", "5 - Guadagno totale");
    int scelta;
    scanf_s("%i", &scelta);
    switch(scelta){

case 1:
    creaBigliettoPasseggero();
    break;
case 2:
    creaBigliettoMacchina();
    break;
case 3:
    printf("%s%i","Il numero totale di biglietti registrati al momento e': ", contaBigliettiTotali());
    break;
case 4:
    passeggeriPerLuogoPartenza();
    break;
case 5:
    printf("%s%i", "Guadagno totale dell'agenzia: ", guadagnoTotale());
    break;
    default:
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
    scanf_s("%15s%15s", _passeggero.nome,15, _passeggero.cognome,15);
    controlloBuffer();
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf_s("%30s%11s%6s", partenza.luogo, 30, partenza.data, 11, partenza.ora, 6);
    controlloBuffer();
    printf("\n%s:\n", "Inserisci luogo, dataa (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf_s("%30s%11s%6s", arrivo.luogo, 30, arrivo.data, 11, arrivo.ora, 6);
    controlloBuffer();

//BIGLIETTO

    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 15;
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

void creaBigliettoMacchina(){
    int a;
    int dimensioniAuto;
    node* head;
    bigliettoMacchina biglietto;
    rotta partenza;
    rotta arrivo;

//INPUT
    printf("%s\n", "Quanti passeggeri nell'auto?");
    scanf_s("%i", &a);
    head = initListaPasseggeri(a);
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf_s("%30s%11s%6s", partenza.luogo,30, partenza.data, 11, partenza.ora, 6);
    controlloBuffer();
    printf("\n%s:\n", "Inserisci luogo, dataa (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf_s("%30s%11s%6s", arrivo.luogo,30, arrivo.data,11, arrivo.ora, 6);
    controlloBuffer();
    printf("\n%s\n", "Inserisci dimensioni auto (m)");
    scanf_s("%i", &dimensioniAuto);





//BIGLIETTO

    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 15 * a + 5; // Numero di passeggeri * 15 + prezzo 5 euro per la macchina.
    biglietto.lunghezza_auto = dimensioniAuto;
    biglietto.head = head;


//SCRITTURA BIGLIETTO SU FILE
    int check = 0;
    FILE* fPtr = ticketsCar(WRITE);
    if(fPtr != NULL){
    fwrite(&a, sizeof(int), 1, fPtr); // INSERISCE NUMERO DI ELEMENTI DELLA LISTA PRIMA DELLA STRUCT
    fwrite(&(biglietto.partenza), sizeof(rotta), 1, fPtr);
    fwrite(&(biglietto.arrivo), sizeof(rotta), 1, fPtr);
    fwrite(&(biglietto.prezzo), sizeof(int), 1, fPtr);
    fwrite(&(biglietto.lunghezza_auto), sizeof(int), 1, fPtr);
    node* temp = head;
    if(temp != NULL){
    while (temp) {
        fwrite(&(temp->_passeggero), sizeof(passeggero), 1, fPtr);
        temp = temp->next;
    }
    fclose(fPtr);
    menu();
    }}else {
        puts("Impossibile aprire il file");
        menu();
    }


}

int contaBigliettiTotali(){

int a = contaBigliettiPasseggero();
int b = contaBigliettiMacchina();
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
    fclose(fPass);
    }else { puts("Impossibile aprire il file"); }

    return count;
}

int contaBigliettiMacchina(){
int temp;
int count = 0;
FILE* fPtr = ticketsCar(READ);
if(fPtr != NULL){
while(fread(&temp, sizeof(int), 1, fPtr) == 1){
    count++;
    fseek(fPtr, sizeof(rotta) * 2 + sizeof(int) * 2 + sizeof(passeggero) * temp, SEEK_CUR);
}
}else {puts("Errore nell'apertura del file"); menu();}
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
        fclose(fPass);
        } else {puts("Nessun biglietto trovato");}

    }
    menu();
}

node* initListaPasseggeri(int numeroPasseggeri){

const node* head = NULL;
aggiungiNodi(&head, numeroPasseggeri);

return head;
}

 void aggiungiNodi(node** head, int numeroNodi) {

    passeggero _passeggero;
    for (int i = 0; i < numeroNodi; i++) {
        node* nuovo = malloc(sizeof(node));
        if (nuovo == NULL) {
            printf("Errore di allocazione memoria.\n");
            menu();
        }
    printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
    scanf_s("%15s%15s", _passeggero.nome, 16, _passeggero.cognome, 16);
    controlloBuffer();
    nuovo->_passeggero = _passeggero;

    nuovo->next = NULL;
        if (*head == NULL) {
            // La lista è vuota, questo è il primo nodo
            *head = nuovo;
        } else {
            // Scorri fino all'ultimo nodo
            node* last = *head;
            while (last->next != NULL) {
                last = last->next;
            }
            last->next = nuovo;
        }
    }
    return;
}

int guadagnoTotale(){
int totale = 0;
int valore = 0;
int temp = 0;
int a = contaBigliettiMacchina();
int b = contaBigliettiPasseggero();
FILE* fPtr = ticketsCar(READ);
if(fPtr != NULL){

    while(fread(&temp, sizeof(int),1, fPtr) == 1){
    fseek(fPtr, sizeof(rotta) * 2, SEEK_CUR);
    fread(&valore, sizeof(int), 1, fPtr);
    totale += valore;
    fseek(fPtr, sizeof(int) + sizeof(passeggero) * temp, SEEK_CUR);

    }
    return totale + 15 * contaBigliettiPasseggero();
}
else {
    puts("Errore nell'apertura del file");
}
}

void passeggeriPerLuogoPartenza(){

passeggero _passeggero;
rotta partenza;
bigliettoMacchina _bigliettoMacchina;
bigliettoPasseggero _bigliettoPasseggero;
printf("\n%s\n", "Inserisci luogo di partenza per cui elencare i passeggeri:");
scanf_s("%30s", partenza.luogo, 30);
printf("\n%s\n", "Lista passeggeri per il luogo di partenza selezionato: ");
puts("Passeggeri biglietto singolo");
//Biglietti Passeggero
int check;
FILE* fPtr1 = ticketsPassenger(READ);
while(fread(&_bigliettoPasseggero, sizeof(bigliettoPasseggero), 1, fPtr1) == 1){
check = 0;
        for(int i = 0; i<lunghezza_luogo; i++){
            if(partenza.luogo[i] != '\0'){
                if(tolower(partenza.luogo[i]) == tolower(_bigliettoPasseggero.partenza.luogo[i])){
                } else { check = 1;}
            } else { break; }
        }
        if(check == 1){
            puts("a");
            } else {

            printf("\n%s\t%s\n", _bigliettoPasseggero.utente.nome, _bigliettoPasseggero.utente.cognome);
            }

      }
            fclose(fPtr1);

//Biglietti Macchina

printf("\n%s\n", "Passeggeri biglietto macchina");
    int num = 0;
    FILE* fPtr2 = ticketsCar(READ);
    while(fread(&num, sizeof(int),1, fPtr2) == 1){

        fread(&_bigliettoMacchina.partenza, sizeof(rotta), 1, fPtr2);
        check = 0;
        for(int i = 0; i<lunghezza_luogo; i++){
            if(partenza.luogo[i] != '\0'){
                if(tolower(partenza.luogo[i]) == tolower(_bigliettoMacchina.partenza.luogo[i])){
                } else { check = 1;}
            } else { break; }
        }
        if(check == 1){

            } else {
            fseek(fPtr2, sizeof(rotta) + sizeof(int) * 2, SEEK_CUR);
            for(int i = 0; i < num; i++){

            fread(&_passeggero, sizeof(passeggero), 1, fPtr2);
            printf("\n%s\t%s\n", _passeggero.nome, _passeggero.cognome);
            }
            }



    }
    fclose(fPtr2);
}

int guadagnoPerGiorno(){








}



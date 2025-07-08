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
int c;
while ((c = getchar()) != '\n' && c != EOF) {

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
    scanf("%i", &scelta);
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
    printf("%s%i", "Guadagno totale dell'agenzia: $", guadagnoTotale());
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
    scanf("%15s%15s", _passeggero.nome, _passeggero.cognome);
    controlloBuffer();
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%30s%11s%6s", partenza.luogo, partenza.data, partenza.ora);
    controlloBuffer();
    controlloDati(partenza.luogo, partenza.data, partenza.ora);
    printf("\n%s:\n", "Inserisci luogo, data (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf("%30s%11s%6s", arrivo.luogo, arrivo.data, arrivo.ora);
    controlloBuffer();
    controlloDati(arrivo.luogo, arrivo.data, arrivo.ora);
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
    int numeroPasseggeri;
    int dimensioniAuto;
    node* head;
    bigliettoMacchina biglietto;
    rotta partenza;
    rotta arrivo;
//INPUT
    printf("%s\n", "Quanti passeggeri nell'auto?");
    scanf("%i", &numeroPasseggeri);
    head = initListaPasseggeri(numeroPasseggeri);
    node* temporaneo = head;
    printf("\n%s:\n", "Inserisci luogo, data(dd-mm-yyyy) e ora(hh-mm) della partenza");
    scanf("%30s%11s%6s", partenza.luogo, partenza.data,partenza.ora);
    controlloBuffer();
    controlloDati(partenza.luogo, partenza.data, partenza.ora);
    printf("\n%s:\n", "Inserisci luogo, dataa (dd-mm-yyyy)e ora (hh-mm) dell'arrivo");
    scanf("%30s%11s%6s", arrivo.luogo, arrivo.data, arrivo.ora);
    controlloBuffer();
    controlloDati(arrivo.luogo, arrivo.data, arrivo.ora);
    printf("\n%s\n", "Inserisci dimensioni auto (m)");
    scanf("%i", &dimensioniAuto);
//BIGLIETTO
    biglietto.partenza = partenza;
    biglietto.arrivo = arrivo;
    biglietto.prezzo = 15 * numeroPasseggeri + 5; // Numero di passeggeri * 15 + prezzo 5 euro per la macchina.
    biglietto.lunghezza_auto = dimensioniAuto;
    biglietto.head = head;
//SCRITTURA BIGLIETTO SU FILE
    FILE* fPtr = ticketsCar(WRITE);
    if(fPtr != NULL){
    fwrite(&numeroPasseggeri, sizeof(int), 1, fPtr); // INSERISCE NUMERO DI ELEMENTI DELLA LISTA PRIMA DELLA STRUCT
    fwrite(&(biglietto.partenza), sizeof(rotta), 1, fPtr);
    fwrite(&(biglietto.arrivo), sizeof(rotta), 1, fPtr);
    fwrite(&(biglietto.prezzo), sizeof(int), 1, fPtr);
    fwrite(&(biglietto.lunghezza_auto), sizeof(int), 1, fPtr);
    if(temporaneo != NULL){
    while (temporaneo) {
        fwrite(&(temporaneo->_passeggero), sizeof(passeggero), 1, fPtr);
        temporaneo = temporaneo->next;
                 }
    fclose(fPtr);
    menu();
                    }
    }else{
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
int contatore = 0;
bigliettoPasseggero biglietto;
    FILE* fPtr = ticketsPassenger(READ);
    if(fPtr != NULL){
    while(fread(&biglietto, sizeof(biglietto), 1, fPtr)){
        contatore++;
            }
    fclose(fPtr);
    }else { puts("Impossibile aprire il file"); }

    return contatore;
}

int contaBigliettiMacchina(){
int temporaneo;
int contatore  = 0;
FILE* fPtr = ticketsCar(READ);
if(fPtr != NULL){
while(fread(&temporaneo, sizeof(int), 1, fPtr) == 1){
    contatore++;
    fseek(fPtr, sizeof(rotta) * 2 + sizeof(int) * 2 + sizeof(passeggero) * temporaneo, SEEK_CUR);
                }
}else {puts("Errore nell'apertura del file"); menu();}
return contatore;
}

void nomiBigliettiPasseggero(){
    bigliettoPasseggero biglietto;
    FILE* fPtr = ticketsPassenger(READ);
    int numeroBigliettiPasseggero = contaBigliettiPasseggero();
    if(fPtr != NULL){
        if(numeroBigliettiPasseggero != 0){
        printf("\n%s\n", "Lista dei nomi biglietti passeggero:");
        for(int i = 0; i < numeroBigliettiPasseggero; i++){
        fread(&biglietto, sizeof(biglietto), 1, fPtr);
        printf("%s%i: %s %s\n", "Utente", i+1, biglietto.utente.nome, biglietto.utente.cognome);
                    }
        fclose(fPtr);
        } else {puts("Nessun biglietto trovato");}
                      }
    menu();
}

node* initListaPasseggeri(int numeroPasseggeri){
node* head = NULL;
aggiungiNodi(&head, numeroPasseggeri);
return head;
}

 void aggiungiNodi(node** head, int numeroNodi) {
    passeggero _passeggero;
    for (int i = 0; i < numeroNodi; i++) {
    node* nuovo = malloc(sizeof(node));
    printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
    scanf("%15s%15s", _passeggero.nome, _passeggero.cognome);
    controlloBuffer();
    nuovo->_passeggero = _passeggero;
    nuovo->next = NULL;
        if (*head == NULL) {
            *head = nuovo;
        } else {
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
else { puts("Errore nell'apertura del file"); }
}

void passeggeriPerLuogoPartenza(){
passeggero _passeggero;
rotta partenza;
bigliettoMacchina _bigliettoMacchina;
bigliettoPasseggero _bigliettoPasseggero;
printf("\n%s\n", "Inserisci luogo di partenza per cui elencare i passeggeri:");
scanf("%30s", partenza.luogo);
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
            } else { printf("\n%s\t%s\n", _bigliettoPasseggero.utente.nome, _bigliettoPasseggero.utente.cognome); }
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

int guadagnoPerGiorno(){ // DA SVOLGERE ANCORA (INSIEME A TANTE ALTRE FUNZIONI DI QUESTO TIPO COME LISTA PASSEGGERI PER ARRIVO ETC)





}

void controlloDati(char luogo[lunghezza_luogo], char data[lunghezza_data],char ora[lunghezza_ora]){
    int j = 0;
    while(luogo[j] != '\0'){
    if(!isalpha(luogo[j])){
        printf("Il luogo di destinazione/partenza e' sbagliato, operazione annullata");
        menu();
    }
    j++;
    }

    char* temporaneo = malloc(sizeof(char));
    int valore;
    int i = 0;
    char* stringa = malloc(sizeof(lunghezza_data));
    stringa = strtok(data, "-");
    while(stringa != NULL){
    valore = strtol(stringa, &temporaneo, 10);
    if(i == 0){
            if(valore < 1 || valore > 31){
            printf("%s\n", "Giorno non corretto, operazione annullata");
            menu();
        }
    }
    if(i == 1){
        if(valore <1 || valore > 12){
            printf("%s\n", "Mese non corretto, operazione annullata");
            menu();
        }
    }
    if(i == 2){
        if(valore <2025 || valore > 2030){
            printf("%s\n", "Anno non corretto, operazione annullata");
            menu();
            }
        }
    stringa = strtok(NULL, "-");
    i++;
    }
    free(stringa);
    stringa = malloc(sizeof(lunghezza_ora));
    stringa = strtok(ora,"-");
    i = 0;
    while(stringa != NULL){
    valore = strtol(stringa, &temporaneo, 10);
    if(i == 0){
            if(valore < 0 || valore > 24){
            printf("%s\n", "Ora non corretta, operazione annullata");
            menu();
        }
    }
    if(i == 1){
        if(valore < 0 || valore > 59){
            printf("%s\n", "Ora non corretta, operazione annullata");
            menu();
        }
        }
    stringa = strtok(NULL, "-");
    i++;
        }
    free(stringa);
    }

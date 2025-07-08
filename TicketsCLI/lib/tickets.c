#include <stdio.h>
#include "../headers/tickets.h"

// Implementazione di strtok_r mancante in MinGW
char* strtok_r(char *str, const char *delim, char **nextp) {
    char *ret;
    if (str == NULL) { str = *nextp; }
    str += strspn(str, delim);
    if (*str == '\0') { return NULL; }
    ret = str;
    str += strcspn(str, delim);
    if (*str) { *str++ = '\0'; }
    *nextp = str;
    return ret;
}

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

// Controlla se il buffer di input contiene caratteri non letti
void controlloBuffer() {
    int a = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { a = 1; }
    if (a) { puts("Input troppo lungo. Operazione annullata"); menu(); }
}

// Mostra il menu principale e gestisce le scelte dell'utente
void menu() {
    while(1) {
        printf("\n\n%s:\n\n%s\n%s\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto Passeggero Singolo", "2 - Crea biglietto passeggeri multipli con macchina");
        printf("%s\n%s\n\%s\n%s\n\n", "3 - Conta Biglietti totali", "4 - Elenco passeggeri per luogo di partenza", "5 - Guadagno totale", "6 - Guadagno per giorno");
        int scelta;
        scanf("%i", &scelta);
        switch(scelta) {
            case 1: creaBigliettoPasseggero(); break;
            case 2: creaBigliettoMacchina(); break;
            case 3: printf("%s%i","Il numero totale di biglietti registrati al momento e': ", contaBigliettiTotali()); break;
            case 4: passeggeriPerLuogoPartenza(); break;
            case 5: printf("%s%i", "Guadagno totale dell'agenzia: $", guadagnoTotale()); break;
            case 6: printf("%s%i", "L'agenzia nel giorno selezionato ha guadagnato $", guadagnoPerGiorno()); break;
            default: break;
        }
    }
}

// Crea un nuovo biglietto per passeggero singolo
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

// Crea un nuovo biglietto per auto con passeggeri multipli
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
            fclose(fPtr);
            menu();
        }
    } else { puts("Impossibile aprire il file"); menu(); }
}

// Conta il numero totale di biglietti (passeggeri + auto)
int contaBigliettiTotali() { return contaBigliettiPasseggero() + contaBigliettiMacchina(); }

// Conta il numero di biglietti passeggero
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

// Conta il numero di biglietti auto
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

// Mostra la lista dei nomi dei passeggeri con biglietto singolo
void nomiBigliettiPasseggero() {
    bigliettoPasseggero biglietto;
    FILE* fPtr = ticketsPassenger(READ);
    int numeroBigliettiPasseggero = contaBigliettiPasseggero();
    if(fPtr != NULL) {
        if(numeroBigliettiPasseggero != 0) {
            printf("\n%s\n", "Lista dei nomi biglietti passeggero:");
            for(int i = 0; i < numeroBigliettiPasseggero; i++) {
                fread(&biglietto, sizeof(biglietto), 1, fPtr);
                printf("%s%i: %s %s\n", "Utente", i+1, biglietto.utente.nome, biglietto.utente.cognome);
            }
            fclose(fPtr);
        } else { puts("Nessun biglietto trovato"); }
    }
    menu();
}

// Inizializza una lista di passeggeri per un biglietto auto
node* initListaPasseggeri(int numeroPasseggeri) {
    node* head = NULL;
    aggiungiNodi(&head, numeroPasseggeri);
    return head;
}

// Aggiunge nodi alla lista di passeggeri
void aggiungiNodi(node** head, int numeroNodi) {
    passeggero _passeggero;
    for (int i = 0; i < numeroNodi; i++) {
        node* nuovo = malloc(sizeof(node));
        printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
        scanf("%15s%15s", _passeggero.nome, _passeggero.cognome);
        controlloBuffer();
        controlloNome(_passeggero);
        nuovo->_passeggero = _passeggero;
        nuovo->next = NULL;
        if (*head == NULL) { *head = nuovo; }
        else {
            node* last = *head;
            while (last->next != NULL) { last = last->next; }
            last->next = nuovo;
        }
    }
    return;
}

// Calcola il guadagno totale dell'agenzia
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

// Mostra i passeggeri in base al luogo di partenza
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
        else { printf("\n%s\t%s\n", _bigliettoPasseggero.utente.nome, _bigliettoPasseggero.utente.cognome); }
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
                printf("\n%s\t%s\n", _passeggero.nome, _passeggero.cognome);
            }
        }
    }
    fclose(fPtr2);
}

// Calcola il guadagno per un giorno specifico
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

// Controlla la sintassi dei dati inseriti (luogo, data, ora)
void controlloDatiSintattico(char luogo[lunghezza_luogo], char data[lunghezza_data], char ora[lunghezza_ora]) {
    int j = 0;
    while(luogo[j] != '\0') {
        if(!isalpha(luogo[j])) {
            printf("Il luogo di destinazione/partenza e' sbagliato, operazione annullata");
            menu();
        }
        j++;
    }
    char data_copia[lunghezza_data];
    char ora_copia[lunghezza_ora];
    strcpy(data_copia, data);
    strcpy(ora_copia, ora);
    char* stringa;
    char* temporaneo;
    int valore;
    int i = 0;
    stringa = strtok(data_copia, "-");
    while(stringa != NULL) {
        valore = strtol(stringa, &temporaneo, 10);
        if(i == 0) {
            if(valore < 1 || valore > 31) {
                printf("%s\n", "Giorno non corretto, operazione annullata");
                menu();
            }
        }
        if(i == 1) {
            if(valore < 1 || valore > 12) {
                printf("%s\n", "Mese non corretto, operazione annullata");
                menu();
            }
        }
        if(i == 2) {
            if(valore < 2025 || valore > 2030) {
                printf("%s\n", "Anno non corretto, operazione annullata");
                menu();
            }
        }
        stringa = strtok(NULL, "-");
        i++;
    }
    i = 0;
    stringa = strtok(ora_copia, "-");
    while(stringa != NULL) {
        valore = strtol(stringa, &temporaneo, 10);
        if(i == 0) {
            if(valore < 0 || valore > 23) {
                printf("%s\n", "Ora non corretta, operazione annullata");
                menu();
            }
        }
        if(i == 1) {
            if(valore < 0 || valore > 59) {
                printf("%s\n", "Minuti non corretti, operazione annullata");
                menu();
            }
        }
        stringa = strtok(NULL, "-");
        i++;
    }
}

// Controlla la validità del nome e cognome del passeggero
void controlloNome(passeggero _passeggero) {
    int j = 0;
    while(_passeggero.nome[j] != '\0') {
        if(!isalpha(_passeggero.nome[j])) {
            printf("Il nome e errato, operazione annullata");
            menu();
        }
        j++;
    }
    j = 0;
    while(_passeggero.cognome[j] != '\0') {
        if(!isalpha(_passeggero.cognome[j])) {
            printf("Il cognome e errato, operazione annullata");
            menu();
        }
        j++;
    }
}

// Controlla la coerenza semantica tra due date
void controlloDataSemantico(char data1[lunghezza_data], char data2[lunghezza_data]) {
    char data_copia_1[lunghezza_data];
    strcpy(data_copia_1, data1);
    char data_copia_2[lunghezza_data];
    strcpy(data_copia_2, data2);
    char* stringa1;
    char* stringa2;
    char* temporaneo1;
    char* temporaneo2;
    char* savePtr1;
    char* savePtr2;
    int valore1, valore2;
    int i = 0;
    stringa1 = strtok_r(data_copia_1, "-", &savePtr1);
    stringa2 = strtok_r(data_copia_2, "-", &savePtr2);
    while(stringa1 != NULL && stringa2 != NULL) {
        valore1 = strtol(stringa1, &temporaneo1, 10);
        valore2 = strtol(stringa2, &temporaneo2, 10);
        if(i == 0) {
            if(valore1 > valore2) {
                printf("%s\n", "Giorno non corretto, operazione annullata");
                menu();
            }
            if(valore2 - valore1 > 2) {
                printf("%s\n", "Il viaggio non puo' richiedere piu' di 2 giorni, operazione annullata");
                menu();
            }
        }
        if(i == 1) {
            if(valore2 - valore1 != 0) {
                printf("%\n%i\t%i\n", valore2, valore1);
                printf("%s\n", "Mesi non coincidono, operazione annullata");
                menu();
            }
        }
        if(i == 2) {
            if(valore1 != valore2) {
                printf("%s\n", "Anni non coincidono, operazione annullata");
                menu();
            }
        }
        stringa1 = strtok_r(NULL, "-", &savePtr1);
        stringa2 = strtok_r(NULL, "-", &savePtr2);
        i++;
    }
}

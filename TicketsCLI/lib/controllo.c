#include <stdio.h>
#include "../headers/controllo.h"

//PERMETTE DI UTILIZZARE STRTOK SU PIU' STRINGHE CONTEMPORANEAMENTE

/**
 * @file controllo.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

/**
 * @pre delim != NULL, nextp puntatore valido
 * @post Modifica str sostituendo i delim con '\0'
 */
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

// CONTROLLA SE IL BUFFER DI INPUT CONTIENE CARATTERI (DATO INSERITO IN SCANF TROPPO LUNGO)
/**
 * @pre Nessuna
 * @post Chiama menu() se trova caratteri nel buffer stdin
 */
void controlloBuffer() {
    int a = 0;
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { a = 1; }
    if (a) { puts("Input troppo lungo. Operazione annullata"); menu(); }
}

// CONTROLLA SE IL TIPO DI DATO INSERITO SEGUE LA FORMATTAZIONE RICHIESTA
/**
 * @pre luogo/data/ora devono essere stringhe valide
 * @post Interrompe l'esecuzione con menu() se dati non validi
 */
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

// CONTROLLA LA VALIDITA' DEL NOME / COGNOME PASSEGGERO (ALFA)
/**
 * @pre _passeggero.nome/cognome non NULL
 * @post Chiama menu() se nome/cognome non alfabetici
 */
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

// CONTROLLA SE LE DATE DI PARTENZA E ARRIVO SONO CORRETTE (NESSUNA TRATTA DURA PIU' DI 2 GIORNI)
/**
 * @pre data1 e data2 nel formato dd-mm-yyyy
 * @post Verifica coerenza temporale (max 2 giorni differenza)
 */
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

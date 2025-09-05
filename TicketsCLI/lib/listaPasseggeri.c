#include <stdio.h>
#include "../headers/filemanager.h"
#include "../headers/listaPasseggeri.h"
#include "../headers/controllo.h"
#include "../headers/menu.h"
#include "../headers/biglietti.h"
#include "../headers/filemanager.h"
#include "../headers/passeggeri.h"

/**
 * @file listaPasseggeri.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

//INIZIALIZZA LA CREAZIONE DELLA LISTA

/**
 * @pre numeroPasseggeri > 0
 * @post Restituisce lista con nodi inizializzati
 */
node* initListaPasseggeri(int numeroPasseggeri) {
    node* head = NULL;
    aggiungiNodi(&head, numeroPasseggeri);
    return head;
}

//AGGIUNGE I NODI ALLA LISTA
/**
 * @pre head puntatore valido, numeroNodi > 0
 * @post Aggiunge nodi alla lista esistente
 */
void aggiungiNodi(node** head, int numeroNodi) {
    passeggero _passeggero;
    for (int i = 0; i < numeroNodi; i++) {
        node* nuovo = malloc(sizeof(node));
        if (nuovo == NULL) {
            fprintf(stderr, "Errore allocazione memoria per nodo\n");
            menu();
        }
        printf("\n%s: \n", "Inserisci nome e cognome del passeggero");
        scanf("%15s%15s", _passeggero.nome, _passeggero.cognome);
        controlloBuffer();
        controlloNome(_passeggero);
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
}
/**
 * @pre Nessuna
 * @post Crea lista con passeggero iniziale
 */
void richiestaAggiunta(){

    int numeroPass=0;
    printf("Quanti passeggeri vuoi aggiungere (oltre al primo)? ");
    scanf("%d", &numeroPass);
    getchar();

    node* head = malloc(sizeof(node));
    if (head == NULL) {
        puts("Errore allocazione memoria.");
        return;
    }

    printf("\nInserisci nome e cognome del primo passeggero:\n");
    scanf("%15s%15s", head->_passeggero.nome, head->_passeggero.cognome);
    controlloBuffer();
    controlloNome(head->_passeggero);

    head->next = NULL;

    aggiungiPasseggerim(&head, numeroPass);
}
/**
 * @pre head punta a lista esistente
 * @post Aggiorna ticketsCar con nuovi passeggeri
 */
void aggiungiPasseggerim(node** head, int numeroPass) {
    if (head == NULL || *head == NULL) {
        printf("Lista passeggeri vuota\n");
        menu();
    }

    FILE* fPtr = ticketsCar(READ_WRITE);
    if (fPtr == NULL) {
        printf("Impossibile aprire il file\n");
        menu();
    }

    int numeroPasseggeri;
    rotta partenza, arrivo;
    int prezzo, lunghezzaAuto;
    long posizioneInizioBiglietto = 0;
    int trovato = 0;

    // Lista temporanea per leggere tutti i passeggeri
    node* listaCompleta = NULL;
    node* tail = NULL;

    while (fread(&numeroPasseggeri, sizeof(int), 1, fPtr) == 1) {
        posizioneInizioBiglietto = ftell(fPtr) - sizeof(int);

        fread(&partenza, sizeof(rotta), 1, fPtr);
        fread(&arrivo, sizeof(rotta), 1, fPtr);
        fread(&prezzo, sizeof(int), 1, fPtr);
        fread(&lunghezzaAuto, sizeof(int), 1, fPtr);

        node* tempList = NULL;
        node* tempTail = NULL;
        int matchTrovato = 0;

        for (int i = 0; i < numeroPasseggeri; i++) {
            passeggero p;
            fread(&p, sizeof(passeggero), 1, fPtr);

            node* nuovo = malloc(sizeof(node));
            if (!nuovo) {
                puts("Errore allocazione memoria.");
                fclose(fPtr);
                return;
            }
            nuovo->_passeggero = p;
            nuovo->next = NULL;

            if (tempList == NULL) {
                tempList = nuovo;
                tempTail = nuovo;
            } else {
                tempTail->next = nuovo;
                tempTail = nuovo;
            }

            // Confronta con il passeggero passato
            if (strcmp(p.nome, (*head)->_passeggero.nome) == 0 &&
                strcmp(p.cognome, (*head)->_passeggero.cognome) == 0) {
                matchTrovato = 1;
            }
        }

        if (matchTrovato) {
            trovato = 1;
            listaCompleta = tempList;
            tail = tempTail;
            break;
        }
    }

    if (!trovato) {
        puts("Biglietto non trovato.");
        fclose(fPtr);
        menu();
    }

    // Aggiungi nuovi passeggeri in fondo alla lista
    for (int i = 0; i < numeroPass; i++) {
        node* nuovo = malloc(sizeof(node));
        if (!nuovo) {
            puts("Errore allocazione memoria.");
            fclose(fPtr);
            puts(" ");
            menu();
            }

        printf("\nInserisci nome e cognome del passeggero \n");
            scanf("%15s%15s", nuovo->_passeggero.nome, nuovo->_passeggero.cognome);
            controlloBuffer();
            controlloNome(nuovo->_passeggero);

            nuovo->next = NULL;
            tail->next = nuovo;
            tail = nuovo;
    }

    // Conta il totale dei passeggeri
    int totale = 0;
    node* temp = listaCompleta;
    while (temp != NULL) {
        totale++;
        temp = temp->next;
    }

    // Riscrivi il biglietto aggiornato nel file
    fseek(fPtr, posizioneInizioBiglietto, SEEK_SET);

    fwrite(&totale, sizeof(int), 1, fPtr);
    fwrite(&partenza, sizeof(rotta), 1, fPtr);
    fwrite(&arrivo, sizeof(rotta), 1, fPtr);
    fwrite(&prezzo, sizeof(int), 1, fPtr);
    fwrite(&lunghezzaAuto, sizeof(int), 1, fPtr);

    temp = listaCompleta;
    while (temp != NULL) {
        fwrite(&temp->_passeggero, sizeof(passeggero), 1, fPtr);
        temp = temp->next;
    }

    puts("Biglietto aggiornato correttamente.");
    fclose(fPtr);
    menu();
}

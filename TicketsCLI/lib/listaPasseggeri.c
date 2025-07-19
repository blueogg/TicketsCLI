#include <stdio.h>
#include "../headers/listaPasseggeri.h"
#include "../headers/controllo.h"
#include "../headers/menu.h"

//INIZIALIZZA LA CREAZIONE DELLA LISTA
node* initListaPasseggeri(int numeroPasseggeri) {
    node* head = NULL;
    aggiungiNodi(&head, numeroPasseggeri);
    return head;
}

//AGGIUNGE I NODI ALLA LISTA
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

//QUALCUNO SCRIVA QUALCHE COSA IN PIU PER LA LISTA NON LO SO INVENTATEVI QUALCOSA ( AD ESEMPIO AGGIUNGERE PASSEGGERI AD UN BIGLIETTO POST CREAZIONE)!!!!!!!!

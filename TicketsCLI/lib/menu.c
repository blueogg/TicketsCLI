#include <stdio.h>
#include "../headers/menu.h"
#include "../headers/filemanager.h"

/**
 * @file menu.c
 * @author Jarno Galesi, Victor Galesi, Mattia di Tondo
 * @date 23/07/2025
 * @version 1.0
 */

// MOSTRA MENU' PRINCIPALE
/**
 * @pre Nessuna
 * @post Gestisce loop infinito fino a scelta uscita (case 11)
 */
void menu() {
    while(1) {
        printf("\n\n%s:\n\n%s\n%s\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto Passeggero Singolo", "2 - Crea biglietto passeggeri multipli con macchina");
        printf("%s\n%s\n\%s\n%s\n%s\n", "3 - Conta Biglietti totali", "4 - Elenco passeggeri per luogo di partenza","5 - Elenco passeggeri per luogo di arrivo", "6 - Guadagno totale", "7 - Guadagno per giorno");
        printf("%s\n%s\n\%s\n", "8 - Elenco completo utenti di tipo passeggero", "9 - Elenco completo utenti di tipo macchina", "10 - Aggiungi passeggeri biglietto macchina");
        printf("%s\n","11 - Chiudi il programma");
        int scelta;
        scanf("%i", &scelta);
        switch(scelta) {
            case 1: creaBigliettoPasseggero(); break;
            case 2: creaBigliettoMacchina(); break;
            case 3: printf("%s%i","Il numero totale di biglietti registrati al momento e': ", contaBigliettiTotali()); break;
            case 4: passeggeriPerLuogoPartenza(); break;
            case 5: passeggeriPerLuogoArrivo(); break;
            case 6: printf("%s%i", "Guadagno totale dell'agenzia: $", guadagnoTotale()); break;
            case 7: printf("%s%i", "L'agenzia nel giorno selezionato ha guadagnato $", guadagnoPerGiorno()); break;
            case 8: nomiBigliettiPasseggero(); break;
            case 9: nomiBigliettiMacchina(); break;
            case 10: richiestaAggiunta(); break;
            case 11: exit(0); break;
            default: break;
        }
    }
}

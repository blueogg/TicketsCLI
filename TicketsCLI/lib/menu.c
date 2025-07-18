#include <stdio.h>
#include "../headers/menu.h"

// MOSTRA MENU' PRINCIPALE
void menu() {
    while(1) {
        printf("\n\n%s:\n\n%s\n%s\n", "Seleziona operazione che vuoi eseguire", "1 - Crea biglietto Passeggero Singolo", "2 - Crea biglietto passeggeri multipli con macchina");
        printf("%s\n%s\n\%s\n%s\n%s\n\n", "3 - Conta Biglietti totali", "4 - Elenco passeggeri per luogo di partenza","5 - Elenco passeggeri per luogo di arrivo", "6 - Guadagno totale", "7 - Guadagno per giorno");
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
            default: break;
        }
    }
}

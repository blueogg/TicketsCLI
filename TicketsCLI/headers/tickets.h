#define lunghezza_data 11
#define lunghezza_ora 6
#define lunghezza_luogo 30
#define lunghezza_nome 15
#define lunghezza_cognome 15

    typedef enum{

    READ = 1,
    WRITE,
    FULL

    }ACCESS;

    typedef struct{

    char luogo[lunghezza_luogo];
    char data[lunghezza_data];
    char ora[lunghezza_ora];

    }rotta;

    typedef struct{

    char nome[lunghezza_nome];
    char cognome[lunghezza_cognome];

    }passeggero;

    typedef struct {

    passeggero _passeggero;
    struct node* next;
        }node;


    typedef struct{

        rotta partenza;
        rotta arrivo;
        int prezzo;
        int lunghezza_auto;
        struct node* head;

    }bigliettoMacchina;

    typedef struct{


        rotta partenza;
        rotta arrivo;
        int prezzo;
        passeggero utente;


    }bigliettoPasseggero;

   FILE* ticketsPassenger(ACCESS _ACCESS); // Restituisce FILE* per i passeggeri.
   FILE* ticketsCar(ACCESS _ACCESS);
   void controlloBuffer();
   void menu();
   void creaBigliettoPasseggero();
   int contaBigliettiPasseggero();
   int contaBigliettiMacchina();
   int contaBigliettiTotali();
   void nomiBigliettiPasseggero();
   node* initListaPasseggeri(int numeroPasseggeri);
   void aggiungiNodi(node** head, int numeroNodi);
   void leggiLista();



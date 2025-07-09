#define lunghezza_data 11
#define lunghezza_ora 6
#define lunghezza_luogo 30
#define lunghezza_nome 15
#define lunghezza_cognome 15

typedef enum {
    READ = 1,
    WRITE,
    FULL
} ACCESS;

typedef struct {
    char luogo[lunghezza_luogo];
    char data[lunghezza_data];
    char ora[lunghezza_ora];
} rotta;

typedef struct {
    char nome[lunghezza_nome];
    char cognome[lunghezza_cognome];
} passeggero;

typedef struct node {
    passeggero _passeggero;
    struct node* next;
} node;

typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    int lunghezza_auto;
    struct node* head;
} bigliettoMacchina;

typedef struct {
    rotta partenza;
    rotta arrivo;
    int prezzo;
    passeggero utente;
} bigliettoPasseggero;

// Funzioni per la gestione dei file
FILE* ticketsPassenger(ACCESS _ACCESS);
FILE* ticketsCar(ACCESS _ACCESS);

// Funzioni per il controllo input
void controlloBuffer();
void controlloDatiSintattico(char luogo[lunghezza_luogo], char data[lunghezza_data], char ora[lunghezza_ora]);
void controlloDataSemantico(char data1[lunghezza_data], char data2[lunghezza_data]);
void controlloNome(passeggero _passeggero);

// Funzioni per la creazione dei biglietti
void creaBigliettoPasseggero();
void creaBigliettoMacchina();
node* initListaPasseggeri(int numeroPasseggeri);
void aggiungiNodi(node** head, int numeroNodi);

// Funzioni per il conteggio
int contaBigliettiPasseggero();
int contaBigliettiMacchina();
int contaBigliettiTotali();

// Funzioni per i report
int guadagnoTotale();
int guadagnoPerGiorno();
void passeggeriPerLuogoPartenza();
void passeggeriPerLuogoArrivo();
void nomiBigliettiPasseggero();

// Funzioni di sistema
void menu();
char* strtok_r(char *str, const char *delim, char **nextp);

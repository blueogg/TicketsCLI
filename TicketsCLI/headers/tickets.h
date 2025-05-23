#define lunghezza_data 10
#define lunghezza_ora 5
#define lunghezza_luogo 30
#define lunghezza_nome 15
#define lunghezza_cognome



    typedef struct{

    char luogo[lunghezza_luogo];
    char data[lunghezza_data];
    char ora[lunghezza_ora];

    }rotta;

    typedef struct{

    char nome[lunghezza_nome];
    char cognome[lunghezza_cognome];

    }passeggero;

    typedef struct{

        rotta partenza;
        rotta arrivo;
        int prezzo;
        int lunghezza_auto;
        // lista passeggeri

    }bigliettoMacchina;

    typedef struct{


        rotta partenza;
        rotta arrivo;
        int prezzo;
        passeggero utente;


    }bigliettoPasseggero;

   void creaBigliettoPasseggero();
   void menu();
   int numeroBigliettiPasseggero();
   void contaBiglietti();
   int numeroBiglietti;



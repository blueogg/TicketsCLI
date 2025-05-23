//In questo file diamo solamente la definizione delle funzioni e degli ADS.


    typedef struct{

    char* luogo;
    char* data;
    char* ora;

    }rotta;

    typedef struct{

    char* nome;
    char* cognome;

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



#ifndef CONTROLLO_H
#define CONTROLLO_H
    #include "./costanti.h"
    #include "./passeggeri.h"
void controlloBuffer();
void controlloNome(passeggero _passeggero);
void controlloDatiSintattico(char luogo[lunghezza_luogo], char data[lunghezza_data], char ora[lunghezza_ora]);
void controlloDataSemantico(char data1[lunghezza_data], char data2[lunghezza_data]);
char* strtok_r(char *str, const char *delim, char **nextp); // (NON PRESENTE IN MINGW, COMPATIBILITA')

#endif

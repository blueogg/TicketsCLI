#ifndef FILEMANAGER_H
#define FILEMANAGER_H

//ENUMERAZIONE TIPO DI ACCESSO

typedef enum {
    READ = 1,
    WRITE,
    FULL
} ACCESS;

FILE* ticketsPassenger(ACCESS _ACCESS);
FILE* ticketsCar(ACCESS _ACCESS);


#endif

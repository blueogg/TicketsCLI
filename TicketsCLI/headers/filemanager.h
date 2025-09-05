#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/**
 * @file filemanager.h
 * @brief Gestione file binari
 */

//ENUMERAZIONE TIPO DI ACCESSO
/**
 * @brief Modalità di accesso ai file
 */
typedef enum {
    READ = 1,
    WRITE,
    FULL,
    READ_WRITE
} ACCESS;
/**
 * @brief Apre ticketsPassengers
 * @param _ACCESS Modalità di apertura
 * @return FILE* o NULL in caso di errore
 */
FILE* ticketsPassenger(ACCESS _ACCESS);
/**
 * @brief Apre ticketsCar
 * @param _ACCESS Modalità di apertura
 * @return FILE* o NULL in caso di errore
 */
FILE* ticketsCar(ACCESS _ACCESS);


#endif

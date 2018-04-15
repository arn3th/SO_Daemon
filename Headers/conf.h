#ifndef CONF_H
#define CONF_H

#include <stdlib.h>
#include <stdio.h>
#include "args.h"
/**
\brief struktura przechowująca dane o ustawieniach
*/
typedef struct {
    char s_dir[FILENAME_MAX];
    char d_dir[FILENAME_MAX];
    long time;
    int r;
    off_t mmap_size;
} conf;

/**
\return zwraca domyślne ustawienia
*/
conf get_conf();

/**
\brief tworzy ustawienia na podstawie argumentów podanych podczas wywołania programu
\details poczatkowo sprawdzane są pierwsze dwa argumenty, czy są katalogami oraz czy nie zawierają się. Następnie pobierane są domyślne ustawienia, a każdy parametr (czas, rozmiar mmap)
jest ustawiony za pomocą poszczególnych funkcji
\return zwraca ustawienia z odpowiednimi wartościami
*/
conf build_config(int, char**);
#endif
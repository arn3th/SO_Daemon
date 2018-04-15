#ifndef ARGS_H
#define ARGS_H

#include <math.h>
#include <string.h>
#include "conf.h"

/**
\brief sprawdza czy znak jest cyfrą
\return zwraca cyfrę
**/
int to_digit(char);

/**
\brief Konwertuje łańuch prezentujący liczbę na liczbę
\return zwraca przekonwertowaną liczbę
**/
int parse(char*);

/**
\brief konwertuje i zapisuje czas podany w parametrach wywołania programu
\return zwraca numer argumentu ostatnio odczytywanego
**/
int set_time(char**, int, int, long int*);

/**
\brief konwertuje i zapisuje rozmiar kopiowania mmap podany w prametrach wywołania programu
\return zwraca numer argumentu ostatnio odczytywanego
**/
int set_mmap(char**, int, int, size_t*);

#endif
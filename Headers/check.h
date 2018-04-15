#ifndef CHECK_H
#define CHECK_H

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <utime.h>
#include <time.h>
#include <syslog.h>

#include "conf.h"

/**
\brief sprawdza czy istnieje katalog o podanej ścieżce
\return zwraca 1 jeśli tak, w przeciwnym przypadku 0
*/
int check_dir(const char*);

/**
\brief sprawdza czy katalogi się zawierają
\details wykorzystuje funkcję strlen, do wyznaczenia krótszej ścieżki, jeśli oba katalogi mają ten sam łańuch znaków w swoich ścieżkach na określonej długości oznacza to, że się zawierają np.
/home
/home/A
na długości pięciu znaków są takie same, więc się zawierają.
\return zwraca 1 jeśli tak, w przeciwnym wypadku 0
*/
int dir_in_dir(const char*, const char*);

/**
\brief sprawdza czy plik o podanej nazwie istnieje
\return zwraca 1 jeśi tak, 0 w przeciwnym przypadku
*/
int exists(char*);

/**
\brief usuwa pliki z katalogu docelowego, których nie ma w źródłowym
\details otwiera plik docelowy i pomijając foldery . i .. tworzy ścieżkę do katalogu źródłowego i wywołuje funkcję sprawdzającą istnienie pliku
jeśli plik nie istnieje to jest usuwany, jeśli plik to folder i należy go usunąć to wywoływana jest funkcją usuwania rekursywnego, po czym usuwa folder
*/
void rm_files(conf);

/**
\brief usuwa rekursywnie wszystko od podanej w parametrze ścieżki
\details otwierany jest katalog podany w ścieżce, każdy plik znajdujący się w katalogu jest wiązany z strukturą 'stat'
jeśli okaże się kolejnym katalogiem to jest funkcja jest wywoływana rekursywnie, jeśli okaże się plikiem to plik jest usuwany,
na koniec następuje zamkniecie czytanego katalogu i jego usunięcie
*/
void recursive_rm(char*);

/**
\return zwraca rozmiar podanego pliku w bajtach
*/
off_t check_size(char*);

/**
\brief sprawdcza czy czasy modyfikacji katalogów takie same
\return zwraca 1 jeśli są różne, 0 jeśli takie same
*/
int compare_time(char*, char*);

/**
\brief zmienia czas modyfikacji pliku docelowego na czas ostatniej modyfikacji pliku źródłowego
\details zamiana czasu polega na wykorzystaniu struktury 'stat' oraz 'utimbuf'. Pierwsza odpowiada za dostarczenie informacji o pliku źródłowym, druga za bufor, który przetrzymuje wartości
obu czasów (mtim oraz atim), utim podstawia czasy z bufora do pliku docelowgo, funkcja chmod użyta w celu zapisania informacji
*/
void change_time(char*, char*);
#endif
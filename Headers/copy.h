#ifndef COPY_H
#define COPY_H

#include <unistd.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <syslog.h>

#include "conf.h"

/**
\brief odpowiada za kopiowanie plików z katalogu źródłowego do docelowego
\details otwierany jest katalog źródłowy, następnie za pomocą struktury 'dirent' czytany jest każdy plik z katalogu oprócz . i .., tworzona jest pełna ścieżka docelowa i źródłowa.
Jeśli plik istnieje w folderze docelowym i posiada on inne czasy modyfikacji niż plik źródłowy to flaga 'copy' jest ustawiana na 1. Jeżeli pliku nie ma w folderze docelowym to ustawiania jest na 1
flaga 'copy' oraz 'create'. Następnie w zależności od tego czy plik jest katalogiem czy zwykłym plikiem i na podstawie flag jest on najpierw tworzony i kopiowany lub tylko kopiowany.
*/
void work(char*, char*, off_t, int);

/**
\brief decyduje, którą opcję kopiowania wybrać
\details jeśli rozmiar pliku źródłowego jest większy niż max_size to wywływane jest kopiowanie za pomocą mapowania
*/
void make_copy(char*, char*, off_t);

/**
\brief kopiowanie zwyczajne za pomocą open() i read()
*/
void copy_normal(char*, char*);

/**
\brief kopiowanie za pomocą mapowaniaw w pamięci
\details oba ppliki otwierane są za pomocą deskryptorów, a następnie za pomocą funkcji mmap zwracane jest  rzeczywiste zamapowanie obiektów,
funkcja trunacte plik docelowy skraca to długości pliku, źródłowego a funkcja memcpy kopiuje oba miejsca, a konkretniej size bajtów. Następnie munmap usuwa mapowanie pliów z pamięci
oraz zamykamy deskryptory.
*/
void copy_mmap(char*, char*);

#endif
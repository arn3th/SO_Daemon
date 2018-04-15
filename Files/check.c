#include "check.h"

/**
\brief sprawdza czy istnieje katalog o podanej ścieżce
\return zwraca 1 jeśli tak, w przeciwnym przypadku 0
*/
int check_dir(const char * name){
    DIR * dir = opendir(name);
    if(dir){
        closedir(dir);
        return 1;
    }
    return 0;
}

/**
\brief sprawdza czy katalogi się zawierają
\details wykorzystuje funkcję strlen, do wyznaczenia krótszej ścieżki, jeśli oba katalogi mają ten sam łańuch znaków w swoich ścieżkach na określonej długości oznacza to, że się zawierają np.
/home
/home/A
na długości pięciu znaków są takie same, więc się zawierają.
\return zwraca 1 jeśli tak, w przeciwnym wypadku 0
*/
int dir_in_dir(const char * src, const char * dest){

    char *path_1, *path_2;
    char buf_1[128], buf_2[128];

    path_1 = realpath(src, buf_1);
    path_2 = realpath(dest, buf_2);
    int l_1 = strlen(path_1);
    int l_2 = strlen(path_2);
    int length = l_1 > l_2 ? l_2 : l_1;
    if(strncmp(path_1, path_2, length) == 0)
        return 1;
    else
        return 0;
}
/**
\brief sprawdza czy plik o podanej nazwie istnieje
\return zwraca 1 jeśi tak, 0 w przeciwnym przypadku
*/
int exists(char * fname)
{
	if(access(fname,F_OK) != -1)
		return 1;
	else
		return 0;
}
/**
\brief usuwa pliki z katalogu docelowego, których nie ma w źródłowym
\details otwiera plik docelowy i pomijając foldery . i .. tworzy ścieżkę do katalogu źródłowego i wywołuje funkcję sprawdzającą istnienie pliku
jeśli plik nie istnieje to jest usuwany, jeśli plik to folder i należy go usunąć to wywoływana jest funkcją usuwania rekursywnego, po czym usuwa folder
*/
void rm_files(conf config)
{
    DIR *dir = opendir(config.d_dir);
	struct dirent *dirent;
    char path[FILENAME_MAX];
    char dest_path[FILENAME_MAX];
	while((dirent = readdir(dir)) != NULL)
	{
		if(strcmp(dirent->d_name,".") == 0 || strcmp(dirent->d_name,"..") == 0)
				continue;

        snprintf(path,FILENAME_MAX,"%s/%s",config.s_dir,dirent->d_name);

		if(!(exists(path)))
		{
            snprintf(dest_path,FILENAME_MAX,"%s/%s",config.d_dir,dirent->d_name);
            if(dirent->d_type == DT_REG)
		        remove(dest_path);
            else if(dirent->d_type == DT_DIR)
                {
                    recursive_rm(dest_path);
                    remove(dest_path);
                }       
		}

        
	}
}
/**
\brief usuwa rekursywnie wszystko od podanej w parametrze ścieżki
\details otwierany jest katalog podany w ścieżce, każdy plik znajdujący się w katalogu jest wiązany z strukturą 'stat'
jeśli okaże się kolejnym katalogiem to jest funkcja jest wywoływana rekursywnie, jeśli okaże się plikiem to plik jest usuwany,
na koniec następuje zamkniecię czytanego folderu i jego usunięcie
*/
void recursive_rm(char* dirname) {

  DIR *d;
  d = opendir(dirname);
  struct dirent *de;
  char path[FILENAME_MAX];
  
  if (d != NULL)
    {
      while (de = readdir (d)) {
        struct stat stFileInfo;

        snprintf(path, FILENAME_MAX, "%s/%s", dirname, de->d_name);

        if (lstat(path, &stFileInfo) < 0)
            perror (path);

        if(S_ISDIR(stFileInfo.st_mode)) {
            if(strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
                //rozpoczynanie usuwania katalogu;
                recursive_rm(path);
          }
        }
        else {
            //usuwanie pliku
            remove(path);
            syslog(LOG_INFO,"Usuwam plik: %s",path);
        }
       }
      (void)closedir(d);
    }
  else
    perror ("Błąd otwarcia katalogu");

  remove(dirname);
  syslog(LOG_INFO,"Usuwam katalog: %s",dirname);

}

/**
\return zwraca rozmiar podanego pliku w bajtach
*/
off_t check_size(char* filename)
{
    struct stat st;
    stat(filename, &st);

    return st.st_size;
}

/**
\brief sprawdcza czy czasy modyfikacji katalogów takie same
\return zwraca 1 jeśli są różne, 0 jeśli takie same
*/
int compare_time(char * src, char * dest)
{
    struct stat st1, st2;
    stat(src, &st1);
    stat(dest, &st2);

    return (st1.st_mtim.tv_sec == st2.st_mtim.tv_sec);
}
/**
\brief zmienia czas modyfikacji pliku docelowego na czas ostatniej modyfikacji pliku źródłowego
\details zamiana czasu polega na wykorzystaniu struktury 'stat' oraz 'utimbuf'. Pierwsza odpowiada za dostarczenie informacji o pliku źródłowym, druga za bufor, który przetrzymuje wartości
obu czasów (mtim oraz atim), utim podstawia czasy z bufora do pliku docelowgo, funkcja chmod użyta w celu zapisania informacji
*/
void change_time(char * src, char * dest)
{
    struct stat st;
    struct utimbuf buf;
    stat(src, &st);
    buf.actime = st.st_atim.tv_sec;
    buf.modtime = st.st_mtim.tv_sec;
    utime(dest, &buf);
    chmod(dest, st.st_mode);
}
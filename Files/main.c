#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <signal.h>
#include <syslog.h>


#include "check.h"
#include "conf.h"
#include "args.h"
#include "daemon.h"
#include "copy.h"

/**
\brief wyświetla pomoc
*/
void help()
{
	printf("Pomoc: readme.txt");
}

/**
\brief obsługuje sygnał SIGUSR1
*/
void handler(int signum)
{
	if(signum == SIGUSR1)
	{
	syslog(LOG_INFO, "Otrzymałem sygnał SIGUSR1");
	}
}


int main(int argc, char *argv[] ){
	
	openlog("DAEMON_SO", LOG_PID, LOG_USER);
	if(argc == 2 && !(strcmp(argv[1],"--help"))) //jeśli wywołano z --help
	{
		help();
		exit(EXIT_SUCCESS);
	}

	signal(SIGUSR1, handler); //ustawienie funkcji obsługującej sygnał SIGUSR1
	conf config = build_config(argc, argv); //stworzenie ustawień na podstawie argumentów
	printf("time = %ld\n", config.time); //wyświetla ustawiony czas
	printf("size = %ld\n",(long int)config.mmap_size); //wyświetla ustawiony minimalny rozmiar
	printf("rec = %d\n", config.r); //wyświetla czy kopiować rekurencyjnie (1 - tak, 0 - nie)

	realpath(argv[1], config.s_dir); //dodanie do ustawień rzeczywistych ścieżek do katalogów
	realpath(argv[2], config.d_dir);

	create_daemon();
   
	while(1)
	{
		syslog(LOG_INFO, "Usypiam na %ld s", config.time); 
		sleep(config.time);		//usypienie demona
		syslog(LOG_INFO, "Wybudzam");
		
		rm_files(config);	//pozbycie się niepotrzebnych plików z katalogu docelowego
		work(config.s_dir, config.d_dir, config.mmap_size, config.r); 	//kopiowanie plików z katalogu źródłowego do docelowego
	} 
	return 0;
	
}

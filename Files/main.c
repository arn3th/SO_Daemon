#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <signal.h>


#include "check.h"
#include "conf.h"
#include "args.h"
#include "daemon.h"

int working = 0;

void help()
{
	printf("Pomoc: źródłowy docelowy \n");
}
void sig()
{
	if(sync)
		printf("Synchronizacja trwa");
	else
		printf("Demon został wybudzony");
}


int main(int argc, char *argv[] ){
	


	if(argc == 2 && argv[1] == "--help")
	{
		help();
		exit(EXIT_SUCCESS);
	}

	int pid = 0; //pid zwracany przez demona
	signal(SIGUSR1, sig);

	if(pid != 0){ //Jeśli zablokowano i zwrócono pid procesu, który blokował
		if(argc == 2 && argv[1] == "-s")
		{
				kill(pid, SIGUSR1);		
		}

		else
		{
			printf("Proszę użyć '-s' aby uruchomić synchronizację");
		}

		exit(EXIT_SUCCESS);
	}
	

	

	conf config = build_config(argc, argv);
	printf("time = %ld\n", config.time);
	printf("size = %ld\n",(long int)config.mmap_size);
	printf("rec = %d\n", config.r);
	config.s_dir = malloc(sizeof(char)*128);
	config.d_dir = malloc(sizeof(char)*128);
    realpath(argv[1], config.s_dir);
    realpath(argv[2], config.d_dir);

	create_daemon();


	//druga blokada?


 	rm_files(config);

	/*while(1)
	{
		//działanie demona
	} */
	return 0;
	
}

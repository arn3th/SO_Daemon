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
#include "copy.h"


void help()
{
	printf("Pomoc: źródłowy docelowy \n");
}

void handler(int signum)
{
	if(signum == SIGUSR1)
	{
	//wpis do logu o rozpoczęciu synchronizacji
	system("touch /home/artwis/SO/signal.txt");
	}
}


int main(int argc, char *argv[] ){
	


	if(argc == 2 && argv[1] == "--help")
	{
		help();
		exit(EXIT_SUCCESS);
	}

	signal(SIGUSR1, handler);
	

	conf config = build_config(argc, argv);
	printf("time = %ld\n", config.time);
	printf("size = %ld\n",(long int)config.mmap_size);
	printf("rec = %d\n", config.r);
	config.s_dir = malloc(sizeof(char)*128);
	config.d_dir = malloc(sizeof(char)*128);
    realpath(argv[1], config.s_dir);
    realpath(argv[2], config.d_dir);

	create_daemon();



 	rm_files(config);

	while(1)
	{
		sleep(config.time);
		//działa demona
	}
	


	

	
	return 0;
	
}

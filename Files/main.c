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
    realpath(argv[1], config.s_dir);
    realpath(argv[2], config.d_dir);

	create_daemon();
	while(1)
	{
		sleep(config.time);
		rm_files(config);
		work(config.s_dir, config.d_dir, config.mmap_size, config.r);
	} 
	

	

	
	return 0;
	
}

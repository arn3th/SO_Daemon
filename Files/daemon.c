#include "daemon.h"

void create_daemon()
{
    pid_t pid;
	int i;

	pid = fork();
	if(pid == -1)
		exit(EXIT_FAILURE);
	else if(pid != 0)
		exit(EXIT_SUCCESS);
	
	if(setsid() == -1)
		exit(EXIT_FAILURE);

	if(chdir("/") == -1)
		exit(EXIT_FAILURE);

	for(i=0; i<3; i++)
		close(i);

	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);
}
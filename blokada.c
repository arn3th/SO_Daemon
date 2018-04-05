#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>
#include <signal.h>


int lock(int lock)
{
    int lock_file = open("/home/artwis/SO/bdssdssdsdl.lock", O_CREAT, O_RDWR, 0666);
    struct flock lockp;
    fcntl(lock_file, F_GETLK, &lockp);
    printf("lock type: %d\n",lockp.l_type);
    if(lockp.l_type == 2){
        lockp.l_type = lock;
        if(fcntl(lock_file, F_SETLKW, &lockp) != -1)
            {
                printf("l.pid: %d\n", (int)lockp.l_pid);
                return 0;
            }
        else return -1;
    }
    else {
        printf("Zablokowano pomyślnie\n");
        return lockp.l_pid;
    }
    
}
void sig_kill()
{
    printf("Powinno zakończyć działanie \n");
    exit(EXIT_SUCCESS);
}
int main()
{

    int pid = lock(0);
    int i;
    signal(SIGTERM, sig_kill);

    if(pid != 0)
    {
        printf("Powinno zabić teraz demona \n");
        printf("uid demona: %d\n",getuid());
	 printf("gid demona: %d\n",getgid());
        kill(pid, SIGTERM);
        return 0;
    }

    printf("Powinno zacząć się tworzenie demona \n");
    pid = fork();
	if(pid == -1)
		{
            printf("Error pid");
            return -1;

        }
	else if(pid != 0)
		exit(EXIT_SUCCESS);

    umask(0);

    printf("pid demona: %d\n",getpid());
     printf("uid demona: %d\n",getuid());
	 printf("gid demona: %d\n",getgid());
	if(setsid() == -1)
		{
            printf("Error setsid");
            return -1;
        }

	if(chdir("/") == -1)
		{
            printf("Error chdir");
            return -1;
        }

	for(i=0; i<3; i++)
		close(i);

/*	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);  */
    

  /*  printf("Lokowanie drugie.\n");
    if(lock(1) != 0)
    {
        printf("Nie można zablokować pliku blokady.");
        exit(EXIT_SUCCESS);
    }   */

    for(int k=0; k<10; k++)
    {
        system("touch /home/artwis/testuje_demona");
        sleep(3);
        system("rm /home/artwis/testuje_demona");
        sleep(3);
    }

    return 0;
}
#include "conf.h"
#include "check.h"

conf get_conf(){
    conf config = { NULL, NULL, 300, 0, 1048576 };
    return config;
    }

conf build_config(int argc, char * argv[])
{

    if(!(check_dir(argv[1]) && check_dir(argv[2])))
		{
            printf("Błąd, to nie są foldery.\n");
            exit(EXIT_FAILURE);
        }
    
    if(dir_in_dir(argv[1],argv[2]))
        {
            printf("Błąd foldery zawierają się.\n");
            exit(EXIT_FAILURE);
        }

	int parameter = 3;
	long int seconds = 0;
    size_t mmap_size = 1;
	int rec = 0;
	while(parameter < argc){
		if(argv[parameter][0] == '-')
		{	
			if(argv[parameter][1] == 't')
				{
				parameter++;
				parameter = set_time(argv, argc, parameter, &seconds)-1;
				}
		     if(argv[parameter][1] == 'p')
			 	{
					parameter++;
					parameter = set_mmap(argv, argc, parameter, &mmap_size)-1;
				 }
			 if(argv[parameter][1] == 'R')
				rec = 1;
		}
		parameter++;
	}


	conf config = {argv[1], argv[2], seconds, rec, mmap_size};

    char buf[128], buff[128];
    config.s_dir = realpath(argv[1], buf);
    config.d_dir = realpath(argv[2], buff);
	return config;
}

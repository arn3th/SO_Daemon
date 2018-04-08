#include "conf.h"
#include "check.h"

conf get_conf(){
    conf config = { "", "", 300, 0, 1048576 };
    return config;
    }

conf build_config(int argc, char * argv[])
{
    conf c = get_conf();

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
	long int seconds = c.time;
    off_t mmap_size = c.mmap_size;
	int rec = 0;
	while(parameter < argc){
		if(argv[parameter][0] == '-')
		{	
			if(argv[parameter][1] == 't')
				{
				parameter++;
                seconds = 0;
				parameter = set_time(argv, argc, parameter, &seconds)-1;
				}
		     if(argv[parameter][1] == 'p')
			 	{
					parameter++;
                    mmap_size = 1;
					parameter = set_mmap(argv, argc, parameter, &mmap_size)-1;
				 }
			 if(argv[parameter][1] == 'R')
				rec = 1;
		}
		parameter++;
	}


	conf config = {"", "", seconds, rec, mmap_size};
	return config;
}

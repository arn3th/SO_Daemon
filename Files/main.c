#include <stdio.h>
#include <stdlib.h>
#include "check.h"
#include "conf.h"
#include "args.h"

int main(int argc, char *argv[] ){
	
	

	if(check_dir(argv[1]) && check_dir(argv[2]))
		printf("To foldery \n");

	conf config = build_config(argc, argv);
	printf("time = %ld\n", config.time);
	printf("size = %ld\n",(long int)config.mmap_size);
	printf("rec = %d\n", config.r);



	return 0;
	
}

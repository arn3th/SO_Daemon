#include <stdio.h>
#include "check.h"

int main(int argc, char *argv[] ){
	
	if(check_dir(argv[1]) && check_dir(argv[2]))
		printf("To foldery");

	printf("%d",argc);
	return 0;
	
}

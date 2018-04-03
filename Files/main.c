#include <stdio.h>
#include <stdlib.h>
#include "check.h"
#include "conf.h"
#include <math.h> //
#include <string.h>//

int to_digit(char ch)
{
	if(ch >= 48 && ch <=57)
		return ch - '0';
	else
		exit(EXIT_FAILURE);
}

int parse(char* ch)
{
	int pt= 0;
	long int res = 0;
	long int seconds = 0;
	for(int i=strlen(ch)-2; i>=0; i--)
		{	res = pow(10,pt++);
			seconds += (to_digit(ch[i]))*res;
		}
	return seconds;
}


int set_time(char *argv[], int argc, int parameter, long int * seconds)
{
	char unit;
	int flag = 1;
	int i = parameter;
	do{
		unit = argv[i][strlen(argv[i])-1];
		switch(unit)
		{
			case 'h':
				(*seconds) += 3600 * parse(argv[i]);
				break;
			case 'm':
				(*seconds) += 60 * parse(argv[i]);
				break;
			case 's':
				(*seconds) += parse(argv[i]);
				break;
			default:
				flag = 0;
				break;
		} i++;
	}while(flag && i < argc); 

	return i;
}


conf build_config(int argc, char * argv[])
{
	int parameter = 3;
	long int seconds = 0;
	while(parameter < argc){
		if(argv[parameter][0] == '-')
		{	
			if(argv[parameter][1] == 't')
				{
				parameter++;
				parameter = set_time(argv, argc, parameter, &seconds)-1;
				}
		     if(argv[parameter][1] == 'p')
			 	printf("Wywołanie mmap");
		
			
		}
		parameter++;
	}
	
	conf config = {NULL, NULL, seconds, 1, 1048576};
	return config;
}

int main(int argc, char *argv[] ){
	
	

	if(check_dir(argv[1]) && check_dir(argv[2]))
		printf("To foldery \n");

	conf config = build_config(argc, argv);
	printf("time = %ld", config.time);


	return 0;
	
}

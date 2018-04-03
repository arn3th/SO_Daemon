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

double parse(char* ch)
{
	int pt= 0;
	double res = 0;
	double seconds = 0;
	for(int i=strlen(ch)-2; i>0; i--)
		{	res = pow(10,pt++);
			seconds += (to_digit(ch[i]))*res;
		}
	printf("Parse");
	return seconds;
}


void set_time(int parameter, char *argv[], conf* config)
{
	char unit;
	do{
		printf("\nParametr: %d\n",parameter);
			return;
		printf("Set time");
	/*	unit = argv[*parameter][strlen(argv[*parameter])-1];
		switch(unit)
		{
			case 'h':
				config->time += 3600 * parse(argv[*parameter]);
				break;
			case 'm':
				config->time += 60 * parse(argv[*parameter]);
				break;
			case 's':
				config->time += parse(argv[*parameter]);
				break;
			default:
				return;
				break;
		} */
	}while((parameter)++);
}

void param(int* parameter, char *argv[], conf* config)
{
	
	if(argv[*parameter][1] == 't')
		{
		printf("Param");
		printf("\nParametr: %d\n",*parameter);
		*parameter++;
		set_time(*parameter, argv, &(*config));
		}
	
	//else if(argv[*parameter][1] == 'm')

		//set_mmap(*parameter, argv, config);

	else if(argv[*parameter][1] == 'R')
		config->r = 1;


}

int main(int argc, char *argv[] ){
	
	int parameter = 3;
	if(check_dir(argv[1]) && check_dir(argv[2]))
		printf("To foldery");

	conf config = get_conf();

	if(argv[parameter][0] == '-')
		param(&parameter, argv, &config);

	printf("%ld\n",config.time);
	printf("%d\n",argc);
	return 0;
	
}

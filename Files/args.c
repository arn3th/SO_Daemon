#include "args.h"
#include <stdio.h>

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

int set_mmap(char* argv[], int argc, int parameter, size_t* mmap_size)
{
	int i = parameter;
	char unit = argv[i][strlen(argv[i])-1];
	switch(unit)
	{
		case 'b':
			(*mmap_size) = parse(argv[i]);
			break;
		case 'k':
			(*mmap_size) = 1024 * parse(argv[i]);
			break;
		case 'm':
			(*mmap_size) = 1024 * 1024 * parse(argv[i]);
			break;
		case 'g':
			(*mmap_size) = 1024*1024*1024 * parse(argv[i]);
			break;
		default:
			break;
	}
	return i+1;
}


#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int* arguments;
int counter = 0;

int main(int argc, char *argv[])
{
	int opt = 0;
	int rdonly = 0;
	
	
	
	int maxAlloc = 1;
	int size = 0;
	
	
	arguments = malloc(sizeof(int));
	if (arguments == NULL)
	{
		fprintf(stderr, "No space of the array");
		exit(1);
	}
	
	static struct option long_options[] = 
	{
		{"rdonly", required_argument, 0, 'r'},
		{0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	opt = getopt_long(argc, argv, "a", long_options, &option_index);
	
	while(opt != -1)
	{
		printf("%d\n", opt);
		printf("i am pobeAFJS:AKFJAS:Flter \n");
		if(size == maxAlloc)
		{
			size++;
			maxAlloc++;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		switch(opt)
		{
			case 'r' :
				arguments[counter] = counter;
				counter++;
				printf("i am pobelter \n");
				printf("%d\n", size);
				printf("%d\n", arguments[counter]);
				break;
		}

		opt = getopt_long(argc, argv, "a", long_options, &option_index);
		printf("%d", opt);
		
	}
	
	exit(0);
}

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
	
	
	arguments = malloc(sizeof(int) * 1000000);
	if (arguments == NULL)
	{
		fprintf(stderr, "No space of the array");
		exit(1);
	}
	
	static struct option long_options[] = 
	{
		{"rdonly", required_argument, 0, 'r'},
		{"wronly", required_argument, 0, 'w'},
		{0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	opt = getopt_long(argc, argv, "a", long_options, &option_index);
	
	int fd;
	
	while(opt != -1)
	{
		if(size == maxAlloc)
		{
			printf("I AM A FAGGOT");
			maxAlloc *= 2;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		switch(opt)
		{
			case 'r' :
				fd = open(optarg, O_RDONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.")
				}
				else
					arguments[counter] = fd
				counter++;
				break;
			case 'w' :
				fd = open(optarg, O_WRONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.")
				}
				else
					arguments[counter] = fd
				arguments[counter] = fd
				counter++;
				break;
		}
		size++;
		opt = getopt_long(argc, argv, "a", long_options, &option_index);
		
	}
	
	exit(0);
}

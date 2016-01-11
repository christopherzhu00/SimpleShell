#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int* arguments;
int counter = 0;
int verboseFlag = 0;

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
		{"verbose", no_argument, 0 , 'v'},
		{"command", required_argument, 0, 'c'}
		{0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	opt = getopt_long(argc, argv, "a", long_options, &option_index);
	
	int fd;
	
	int iterator;
	int option_index_placeholder = 0;
	
	while(opt != -1)
	{
		if(size == maxAlloc)
		{
	//		printf("I AM A FAGGOT\n");
			maxAlloc *= 2;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		
		
		option_index_placeholder = optind - option_index_placeholder;
	//	printf("THE OPTION INDEX IS: %d\n", optind);
	//	printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
		switch(opt)
		{
			
			case 'r' :
				if(verboseFlag)
				{
		//			printf("i hate life\n");

			//		printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
					for(iterator = 0; iterator < 2; iterator++)
					{
						printf("%s ", argv[option_index_placeholder + iterator]);
					}
					printf("\n");
				}
				fd = open(optarg, O_RDONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.");
				}
				else
					arguments[counter] = fd;
				counter++;
				break;
			case 'w' :
				if(verboseFlag)
				{
		//			printf("i hate life\n");

			//		printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
					for(iterator = 0; iterator < 2; iterator++)
					{
						printf("%s ", argv[option_index_placeholder + iterator]);
					}
					printf("\n");
				}
				fd = open(optarg, O_WRONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.");
				}
				else
					arguments[counter] = fd;
				counter++;
				break;
			
			case 'v' :
				verboseFlag = 1;
				printf("FLAG HAS BEEN SET\n");
				break;
				
			case 'c'
				pid_t Child_PID = fork(); 
				if (Child_PID == 0) { 
					//its a child
				}
				else if (Child_PID > 0) {
					//its a parent
				}
				else {
					//shit hit the fan
					printf("Messed up forking"); 
					exit(1); 
				}
		}
		size++;
	//	printf("THE OPTION INDEX IS: %d\n", optind);
		opt = getopt_long(argc, argv, "a", long_options, &option_index);
	//	printf("THE OPTION INDEX IS: %d\n", optind);
	}
	
	exit(0);
}

#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

int* arguments;
int counter = 0;
int verboseFlag = 0;


int main(int argc, char *argv[])
{
	int opt = 0;
	int rdonly = 0;
	
	int command_arg[3];
	int command_counter = 0;
	char* all_command_values;
	
	
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
		{"command", required_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
	
	int option_index = 0;
	
	opt = getopt_long(argc, argv, "a", long_options, &option_index);
	
	int fd;
	
	int iterator;
	int option_index_placeholder = 0;	// holds the index of the current option 
	int argument_index;				// holds the index of the argument
	
	int size_of_argument1 = 0;
	int size_of_argument2 = 0;
	int size_of_argument3 = 0;
	
	
	int failure = 0;
	int z;
	int i;
	int fileD;
	int current = 1;
//	char*
	int SIZEOFARRAY;
//	int child = 0;
	while(opt != -1)
	{
		if(size == maxAlloc)
		{
	//		printf("I AM A FAGGOT\n");
			maxAlloc *= 2;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		
	//	printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
		printf("THE OPTION INDEX IS: %d\n", optind);
	//	option_index_placeholder = (optind - option_index_placeholder);
//		printf("THE OPTION CURRENT IS: %d\n", current);
//		printf("THE OPTION INDEX IS: %d\n", optind);
//		printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
		//printf("IN THE SWITCH NOW BOYS \n");
		int maxChars = 100; 
		char** commandArgs; 
		switch(opt)
		{
			
			case 'r' :
				if(verboseFlag)
				{
			//		printf("i hate life\n");
			//		printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
					for(iterator = 0; iterator < 2; iterator++)
					{	
			//			printf("%s ", argv[optind + iterator - 2]);
						printf("%s ", argv[current + iterator]);
					}
					printf("\n");
				}
				fd = open(optarg, O_RDONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.");
				}
				else
				{
					arguments[counter] = fd;
					//printf("fd is: %d\n", fd);
					//printf("counter is: %d\n", counter);
					//printf("THE VALUE IN THE THIGNY IS %d\n", arguments[counter]);
				}
				current +=2;
				counter++;
				
				break;
			case 'w' :
				if(verboseFlag)
				{
		//			printf("i hate life\n");

			//		printf("THE OPTION INDEX placeholder IS: %d\n", option_index_placeholder);
					for(iterator = 0; iterator < 2; iterator++)
					{
				//		printf("%s ", argv[optind + iterator - 2]);
						printf("%s ", argv[current + iterator]);
					}
					printf("\n");				// BE SURE TO TAKE THIS OUT LATER MAYBE?>?!?!?!?!?!?!?!!?!??????????????????????????????????????
				}
				fd = open(optarg, O_WRONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.");
				}
				else
					arguments[counter] = fd;
				counter++;
				current+=2;
				break;
			
			case 'v' :
				verboseFlag = 1;
				//printf("FLAG HAS BEEN SET\n");
				current++;
				break;
				
			case 'c' : 

			
			commandArgs = malloc(sizeof(char*)*maxChars); 
			int memoryCount = 0; 
			int innerMemory = 100; 
			for(memoryCount = 0; memoryCount < maxChars; memoryCount++) {
				commandArgs[memoryCount] = malloc(sizeof(char)*innerMemory); 
			}
			int count = 0; 
			int place = current+1;
			int doubleDash = 0; 
			 
			while(!doubleDash && argv[place]!=NULL) { 
				if(argv[place][0] == '-') { 
					if(argv[place][1] == '-') {
						doubleDash = 1; 
						break; 
					}
				}
				if(count == maxChars) {
					maxChars *= 2; 
					commandArgs = realloc(commandArgs, maxChars); 
				}
				int secondSpot = 0; 
				while(argv[place][secondSpot] != '\0') {
					if(secondSpot == innerMemory) {
						innerMemory *= 2; 
						commandArgs[count] = realloc(commandArgs[count], innerMemory*sizeof(char)); 
					}
					commandArgs[count][secondSpot] = argv[place][secondSpot]; 
					secondSpot++; 
				}
				innerMemory = 100; 
				count++; 
				place++; 
			}
			int j; 
			int k; 
			for(j = 0; j<count; j++) {
				int k =0; 
				printf("the command is: "); 
				while(commandArgs[j][k]!='\0') {
					printf("%c", commandArgs[j][k]); 
					k++; 
				}
				printf("\n"); 
			}
			 
			// special case since option_index_placeholder stores the next command beginning and not its arguments
			
			// CURRENT HOLDS INDEX AT COMMAND
			// PRINTS THROUGH THE ARRAY IF VERBOSE IS ON
			// CURRENT += size of array
			// 
			
			if(verboseFlag)
			{
											//SIZE
				for(iterator = 0; iterator < count+1; iterator++)
				{
					printf("%s ", argv[current + iterator]);
				}
				printf("\n");
			}
			//error checking to see if they put in enough stuff (commmand 0 1 2 blah)
			if(count < 4)
			{
				fprintf(stderr, "Error in arguments. Not enough arguments.\n");
				break;
			}
						//THE NEW ARRAY
			for(i = 0; commandArgs[0][i] != '\0'; i++)
			{
				size_of_argument1++;
			}				//UPDATE
			for(i = 0; commandArgs[1][i] != '\0'; i++)
			{
				size_of_argument2++;
			}			//UPDATE
			for(i = 0; commandArgs[2][i] != '\0'; i++)
			{
				size_of_argument3++;
			}
			
			
			for(z = 0; z < size_of_argument1; z++)
			{
					//NEW CREATED ARRAY
				if(!(isdigit(commandArgs[0][z])))
					{
						fprintf(stderr, "Error in arguments. Invalid argument.");
						break;
					}
			}
			for(z = 0; z < size_of_argument2; z++)
			{					//UPDATE
				if(!(isdigit(commandArgs[1][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.");
					break;
				}
			}
			for(z = 0; z < size_of_argument3; z++)
			{					//UPDATE
				if(!(isdigit(commandArgs[2][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.");
					break;
				}
			}
			
								//UPDATE THIS ONE TOO
			command_arg[0] = atoi(commandArgs[0]);
			command_arg[1] = atoi(commandArgs[1]);
			command_arg[2] = atoi(commandArgs[2]);
				
	//			printf("DONEZO\n");

			size_of_argument1 = 0;
			size_of_argument2 = 0;
			size_of_argument3 = 0;		

			// MIGHT NEED TO UPDATE
			current += (count+1);
			
			
//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA			
/*			if(verboseFlag)
				{
					
					for(iterator = 0; iterator < 2; iterator++)
					{
						printf("the iterator is: %d\n", iterator); 
	//					printf("%s ", argv[option_index_placeholder + iterator]);
					}
					printf("\n");	
					argument_index = optind + 1;		
				}
				else
				{
					argument_index = optind - 1;
				}

				//printf("argument_index is: %d\n", argument_index);
				
				//printf("IM GOIN IN\n");
				//printf("arg c: %d\n", argc);
				//printf("optind: %d\n", optind);
				if(argument_index + 3 >= argc)
				{
					fprintf(stderr, "Error in arguments. Not enough arguments.\n");
					break;
				}
				
				
				for(i = 0; argv[argument_index][i] != '\0'; i++)
				{
					size_of_argument1++;
				}
				for(i = 0; argv[argument_index + 1][i] != '\0'; i++)
				{
					size_of_argument2++;
				}
				for(i = 0; argv[argument_index + 2][i] != '\0'; i++)
				{
					size_of_argument3++;
				}
			//printf("size of  arg1: %d\n", size_of_argument1);
			//printf("size of  arg2: %d\n", size_of_argument2);
			//printf("size of  arg3: %d\n", size_of_argument3);

					for(z = 0; z < size_of_argument1; z++)
					{
						if(!(isdigit(argv[argument_index][z])))
						{
							fprintf(stderr, "Error in arguments. Invalid argument.");
							break;
						}
					}
					for(z = 0; z < size_of_argument2; z++)
					{
						if(!(isdigit(argv[argument_index+1][z])))
						{
							fprintf(stderr, "Error in arguments. Invalid argument.");
							break;
						}
					}
					for(z = 0; z < size_of_argument3; z++)
					{
						if(!(isdigit(argv[argument_index+2][z])))
						{
							fprintf(stderr, "Error in arguments. Invalid argument.");
							break;
						}
					}
				printf("THE INT IN COMMANDARG0 is: %d\n", atoi(argv[argument_index]));
				printf("THE INT IN COMMANDARG1 is: %d\n", atoi(argv[argument_index + 1]));
				printf("THE INT IN COMMANDARG2 is: %d\n", atoi(argv[argument_index + 2]));
				command_arg[0] = atoi(argv[argument_index]);
				command_arg[1] = atoi(argv[argument_index + 1]);
				command_arg[2] = atoi(argv[argument_index + 2]);
				
	//			printf("DONEZO\n");

				size_of_argument1 = 0;
				size_of_argument2 = 0;
				size_of_argument3 = 0;				
				
				/*for(i = 0; i < 3; i++)
	{
		printf("COMMAND arguments value is :%d\n", command_arg[i]);
	}*/
				
				
				//printf("EXECUTORS\n");
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@2@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//PUT IN HERE 
				//optind+= count-2 to factor in special case
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				
				
				
				
				pid_t Child_PID = fork(); 
				//printf("THE CHILDPID IS: %d", Child_PID);
				if (Child_PID == 0) { 
					//its a child
				//printf("egg\n");
				//fprintf(stderr, "EXECUTOR\n");
	//			child = 1;
					for(i = 0; i < 3; i++)
					{
						fileD = command_arg[i];
						printf("The command arg is: %d\n", command_arg[i]); 
						printf("GET IN HERE\n");
						dup2(arguments[fileD], i);
					}
				
					printf("THE STRING IN ARGV is: %s\n", argv[argument_index + 3]);
								//UPDATE THIS WITH NEW ARRAY
					execvp(commandArgs[3], &commandArgs[3]);
					printf("%d\n", errno);
					perror(NULL);
				}
				else if (Child_PID > 0) {
					//its a parent
				}
				else {
					//shit hit the fan
					printf("Messed up forking"); 
					exit(1); 
				}
				break;
		}
		size++;
		
	//	arg_counter = 0;
		
		
	//	printf("THE OPTION INDEX IS: %d\n", optind);
//		printf("OPT IS : %d\n", opt);
//		printf("OPTind IS : %d\n", optind);
		opt = getopt_long(argc, argv, "a", long_options, &option_index);
		
	//	printf("THE OPTION INDEX IS: %d\n", optind);
	}
	//printf("counter IS: %d\n", counter);
	/*for(i = 0; i < 3; i++)
	{
		printf("arguments value is :%d\n", arguments[i]);
	}*/
/*	for(i = 0; i < sizeof(arguments)/sizeof(int); i++) {
					printf("The argument is: %d\n", arguments[i]); 
				}
					*/
					//fprintf(stderr, "EXECUTOR\n");
	exit(0);
}



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
int ret = 0;
int current = 1;
int curCount;
void verbosePrint(char *argv[], int curCount, int current); 
void fileFunction(char *argv[], int flag);


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
	
	//int fd;
	
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
	
	int SIZEOFARRAY;
	  
	int fd; 

	while(opt != -1)
	{
		if(size == maxAlloc)
		{
	//		printf("I AM A FAGGOT\n");
			maxAlloc *= 2;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		int maxChars = 100; 
		char** commandArgs; 
		switch(opt)
		{
			case 'r' :
				fileFunction(argv, O_RDONLY); 
			/*
				curCount = 1; 
				for(;;){
					if(argv[current+curCount] == '\0'){ 
						break; 
					}
					else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
						break; 
					curCount++; 
				}
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current); 
				}

				if(curCount != 2){ 
					fprintf(stderr, "Incorrect number of arguments\n"); 
					ret =1; 
				}

				fd = open(optarg, O_RDONLY);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.\n");
					ret =1; 
				}
				else
				{
					arguments[counter] = fd;
				}
				current +=curCount;
				counter++;
				*/
				break;
			case 'w' :
				fileFunction(argv, O_WRONLY); 
				/*curCount = 1; 
				for(;;){
					if(argv[current+curCount] == '\0'){ 
						break; 
					}
					else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
						break; 
					curCount++; 
				}
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current);		// BE SURE TO TAKE THIS OUT LATER MAYBE?>?!?!?!?!?!?!?!!?!??????????????????????????????????????
				}

				if(curCount != 2){ 
					fprintf(stderr, "Incorrect number of arguments\n"); 
					ret =1; 
				}

				fd = open(optarg, yes);
				if(fd == -1)
				{
					fprintf(stderr, "Error in opening file.\n");
					ret =1; 
				}
				else
					arguments[counter] = fd;
				counter++;
				current+=curCount;
				*/
				break;
			
			case 'v' :
				curCount = 1; 
				for(;;){
					if(argv[current+curCount] == '\0'){ 
						break; 
					}
					else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
						break; 
					curCount++; 
				}
				if(verboseFlag)
				{
					/*for(iterator = 0; iterator < curCount; iterator++)
					{
						printf("%s", argv[current + iterator]);
						if(iterator != curCount-1) {
							printf(" "); 
						}
					}
					printf("\n");*/
					verbosePrint(argv, curCount, current); 				// BE SURE TO TAKE THIS OUT LATER MAYBE?>?!?!?!?!?!?!?!!?!??????????????????????????????????????
				}
				if(curCount != 1){ 
					fprintf(stderr, "Incorrect number of arguments\n"); 
					ret =1; 
				}
				verboseFlag = 1;
				current+=curCount;
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
					if(!commandArgs){
						fprintf(stderr, "Error allocating memory.\n"); 
						ret=1; 
					}
				}
				int secondSpot = 0; 
				while(argv[place][secondSpot] != '\0') {
					if(secondSpot == innerMemory) {
						innerMemory *= 2; 
						commandArgs[count] = realloc(commandArgs[count], innerMemory*sizeof(char)); 
						if(!commandArgs[count]){ 
							fprintf(stderr, "Error allocating memory.\n"); 
							ret =1; 
						}
					}
					commandArgs[count][secondSpot] = argv[place][secondSpot]; 
					secondSpot++; 
				}
				innerMemory = 100; 
				count++; 
				place++; 
			}
			if(count == maxChars) {
				commandArgs = realloc(commandArgs, sizeof(char*)*(maxChars+1)); 
				if(!commandArgs) {
					fprintf(stderr, "Error allocating memory.\n"); 
					ret = 1; 
				}
			}
			commandArgs[count] = NULL;  
			 
			// special case since option_index_placeholder stores the next command beginning and not its arguments
			
			// CURRENT HOLDS INDEX AT COMMAND
			// PRINTS THROUGH THE ARRAY IF VERBOSE IS ON
			
			if(verboseFlag)
			{
											//SIZE
				/*for(iterator = 0; iterator < count+1; iterator++)
				{
					printf("%s", argv[current + iterator]);
					if(iterator != count) { 
						printf(" ");
					}
				}
				printf("\n");*/
				verbosePrint(argv, count+1, current); 
			}
			
			//error checking to see if they put in enough stuff (commmand 0 1 2 blah)
			if(count < 4)
			{
				fprintf(stderr, "Error in arguments. Not enough arguments.\n");
				ret =1;  
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				continue;
			}
						//THE NEW ARRAY 
			for(i = 0; commandArgs[0][i] != '\0'; i++)
			{ 
				size_of_argument1++;
			}
			
 			//UPDATE
			for(i = 0; commandArgs[1][i] != '\0'; i++)
			{
				size_of_argument2++;
			}	
	 		//UPDATE
			for(i = 0; commandArgs[2][i] != '\0'; i++)
			{
				size_of_argument3++;
			}
			
			
			for(z = 0; z < size_of_argument1; z++)
			{              //NEW CREATED ARRAY
				if(!(isdigit(commandArgs[0][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.\n");
					ret = 1; 
				}
					
				
			}
			for(z = 0; z < size_of_argument2; z++)
			{						//UPDATE
			if(!(isdigit(commandArgs[1][z])))
				{
				fprintf(stderr, "Error in arguments. Invalid argument.\n");
					ret =1; 
				}
			}
			for(z = 0; z < size_of_argument3; z++)
			{					//UPDATE
			if(!(isdigit(commandArgs[2][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.\n");
					ret =1; 
				}
			}
			
			if (ret == 1){
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				continue;
			}
			
								//UPDATE THIS ONE TOO
			command_arg[0] = atoi(commandArgs[0]);
			command_arg[1] = atoi(commandArgs[1]);
			command_arg[2] = atoi(commandArgs[2]);

			size_of_argument1 = 0;
			size_of_argument2 = 0;
			size_of_argument3 = 0;		

			// MIGHT NEED TO UPDATE
			current += (count+1);

			optind+= count-1; 
				
				
				pid_t Child_PID = fork(); 
				if (Child_PID == 0) { 
					
					for(i = 0; i < 3; i++)
					{
						fileD = command_arg[i];
						dup2(arguments[fileD], i);
					}
								//UPDATE THIS WITH NEW ARRAY
					execvp(commandArgs[3], &commandArgs[3]);
				}
				else if (Child_PID > 0) {
					//its a parent
				}
				else {
					//shit hit the fan
					printf("Messed up forking.\n"); 
					ret =1; 
				}
				break;
		}
		size++;
		
		opt = getopt_long(argc, argv, "a", long_options, &option_index);
	}
	exit(ret);
}

void verbosePrint(char *argv[], int curCount, int current) {
	int iterator; 
	for(iterator = 0; iterator < curCount; iterator++)
	{
		printf("%s", argv[current + iterator]);
		if(iterator != curCount-1) { 
			printf(" ");
		}
	}
	printf("\n");
}


void fileFunction(char *argv[], int flag) { 
	curCount = 1; 
	for(;;){
		if(argv[current+curCount] == '\0'){ 
			break; 
		}
		else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
			break; 
		curCount++; 
	}
	if(verboseFlag)
	{
		verbosePrint(argv, curCount, current); 
	}

	if(curCount != 2){ 
		fprintf(stderr, "Incorrect number of arguments\n"); 
		ret =1; 
	}

	int fd = open(optarg, flag);
	if(fd == -1)
	{
		fprintf(stderr, "Error in opening file.\n");
		ret =1; 
	}
	else
	{
		arguments[counter] = fd;
	}
	current +=curCount;
	counter++;

}



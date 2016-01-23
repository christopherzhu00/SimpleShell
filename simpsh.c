#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

int* arguments;
int counter = 0;
int verboseFlag = 0;
int ret = 0;
int current = 1;
int curCount;
int optionalFlags = 0; 
void verbosePrint(char *argv[], int curCount, int current); 
void fileFunction(char *argv[], int flag);
void flagModifier(int option, char *argv[]); 


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
		
		
		
		{"abort", no_argument, 0, 'a'},
		{"nonblock", no_argument, 0, 'b'},
		{"command", required_argument, 0, 'c'},
		{"directory", no_argument, 0, 'd'},
		{"excl", no_argument, 0, 'e'},
		{"rdwr", required_argument, 0, 'f'},
		{"cloexec", no_argument, 0, 'l'}, 
		{"creat", no_argument, 0, 'm'},
		{"nofollow", no_argument, 0, 'n'},
		{"append", no_argument, 0, 'p'},
		{"rsync", no_argument, 0, 'q'},
		{"rdonly", required_argument, 0, 'r'},
		{"rsync", no_argument, 0, 's'},
		{"trunc", no_argument, 0. 't'},
		{"verbose", no_argument, 0 , 'v'},
		{"wronly", required_argument, 0, 'w'},
		{"dsync", no_argument, 0, 'y'},
		 
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
			maxAlloc *= 2;
			arguments = realloc(arguments, maxAlloc * sizeof(char));	
		}			
		
		int maxChars = 100; 
		char** commandArgs; 
		switch(opt)
		{
			case 'a' :
				curCount = 1;
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current); 		
				}
				raise(SIGSEGV);

			case 'r' :
				fileFunction(argv, O_RDONLY); 
				break;
			
			case 'w' :
				fileFunction(argv, O_WRONLY); 
				break;

			case 'f':
				fileFunction(argv, O_RDWR); 
				break;

			case 'p': 
				flagModifier(O_APPEND, argv); 
				break; 

			case 'l':
				flagModifier(O_CLOEXEC, argv); 
				break; 

			case 'm':
				flagModifier(O_CREAT, argv); 
				break; 

			case 'd':
				flagModifier(O_DIRECTORY, argv); 
				break; 

			case 'y': 
				flagModifier(O_DSYNC, argv); 
				break; 

			case 'e':
				flagModifier(O_EXCL, argv); 
				break; 

			case 'n':
				flagModifier(O_NOFOLLOW, argv); 
				break; 

			case 'b':
				flagModifier(O_NONBLOCK, argv); 
				break; 

			case 'q':
				flagModifier(O_RSYNC, argv); 
				break; 

			case 's':
				flagModifier(O_SYNC, argv); 
				break; 

			case 't':
				flagModifier(O_TRUNC, argv); 
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
	
	flag |= optionalFlags; 
	int fd = open(optarg, flag);
	optionalFlags = 0; 
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

void flagModifier(int option, char *argv[]) { 
	if(verboseFlag) {
		verbosePrint(argv, curCount, current); 
	}
	optionalFlags |= option; 
	current++; 
}



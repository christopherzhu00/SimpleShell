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
void sig_handler(int signum);


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
	
	enum flag
		{
			flag1,
			flag2,
			flag3,
			flag4,
			flag5,
			flag6,
			flag7,
			flag8,
			flag9,
			flag10,
			flag11,
		};
		
	static struct option long_options[] = 
	{
		{"abort", no_argument, 0, 'a'},
		{"nonblock", no_argument, 0, flag8},
		{"command", required_argument, 0, 'c'},
		{"directory", no_argument, 0, flag4},
		{"excl", no_argument, 0, flag6},
		{"rdwr", required_argument, 0, 'f'},
		{"cloexec", no_argument, 0, flag2}, 
		{"creat", no_argument, 0, flag3},
		{"nofollow", no_argument, 0, flag7},
		{"append", no_argument, 0, flag1},
		{"rsync", no_argument, 0, flag9},
		{"rdonly", required_argument, 0, 'r'},
		{"sync", no_argument, 0, flag10},
		{"trunc", no_argument, 0, flag11},
		{"pause", no_argument, 0, 'g'}, 
		{"close", required_argument, 0, 'u'}, 
		{"verbose", no_argument, 0 , 'v'},
		{"wronly", required_argument, 0, 'w'},
		{"dsync", no_argument, 0, flag5},
		{"wait", required_argument, 0, 'w'},		// 1/24
		{"ignore", required_argument, 0, 'i'},
		{"default", required_argument, 0, 'd'},
		{"catch", required_argument, 0 , 't'},
		 
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
	int signum;
	
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
			case 'd' :
			//	printf("%s\n", argv[current + 1]);
				
				signum = atoi(argv[current + 1]);
			//	printf("%d\n", signum);
				signal(signum, SIG_DFL);
				break;
		
			case 'i' :
				signum = atoi(argv[current + 1]);
				signal(signum, SIG_IGN);
				break;
				
			case 't' :		// catch
				signum = atoi(argv[current + 1]);
				signal(signum, sig_handler(signum));
				break;
				
		
	/*		case 'w' :
			//ITS JUST A THEORY
				int status;
				int exit_Value;
				for(i = 0; i < counter; i++)
				{
					waitpid(-1, &status, 0)				
					if(WIFEXITED(status))
					{
						exit_Value = WEXITSTATUS(status);
						//print out the shit
					}
				}*/
				
			case 'r' :
				fileFunction(argv, O_RDONLY); 
				break;
			
			case 'w' :
				fileFunction(argv, O_WRONLY); 
				break;

			case 'f':
				fileFunction(argv, O_RDWR); 
				break;

			case flag1: 
				flagModifier(O_APPEND, argv); 
				break; 

			case flag2:
				flagModifier(O_CLOEXEC, argv); 
				break; 

			case flag3:
				flagModifier(O_CREAT, argv); 
				break; 

			case flag4:
				flagModifier(O_DIRECTORY, argv); 
				break; 

			case flag5: 
				flagModifier(O_DSYNC, argv); 
				break; 

			case flag6:
				flagModifier(O_EXCL, argv); 
				break; 

			case flag7:
				flagModifier(O_NOFOLLOW, argv); 
				break; 

			case flag8:
				flagModifier(O_NONBLOCK, argv); 
				break; 

			case flag9:
				flagModifier(O_RSYNC, argv); 
				break; 

			case flag10:
				flagModifier(O_SYNC, argv); 
				break; 

			case flag11:
				flagModifier(O_TRUNC, argv); 
				break; 	

			case 'g':
				curCount = 1; 
				if(verboseFlag) 
					verbosePrint(argv, curCount, current); 
				pause(); 
				break; 

			case 'u':
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
				verbosePrint(argv, curCount, current); 
			int N = atoi(argv[current+1]); 
			printf("the char value is: %s\n", argv[current+1]); 
			printf("the int value is %d\n", N); 
			close(arguments[N]); 
			//current+=2; 
			current += curCount; 
			//counter++; 

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
				size++; 
				current += (count+1);
				continue;
			}
			
								//UPDATE THIS ONE TOO
			command_arg[0] = atoi(commandArgs[0]);
			command_arg[1] = atoi(commandArgs[1]);
			command_arg[2] = atoi(commandArgs[2]);
			
			/*for(i = 0; i < 3; i++)
			{
				if(command_arg[i] > counter)
				{
					fprintf(stderr, "Error in arguments. Not enough file descriptors.\n");
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					continue;
				}
			}*/
			

			for(z=0; z < 3; z++) {
				int open = fcntl(command_arg[z], F_GETFL); 
				if(open < 0 || errno == EBADF) {
					fprintf(stderr, "Error: Accessing nonopen file descriptor\n"); 
					ret = 1; 
					//size++; 
					//current += (count+1);
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					continue; 
				}
			}

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

void sig_handler(int signum)
{
	fprintf(stderr, "The diagnostic signal is: %d", signum);
	exit(signum);
}



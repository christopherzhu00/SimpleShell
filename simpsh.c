#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>

int* fdTable;
int counter = 0;
int childCounter = 0;
int verboseFlag = 0;
int ret = 0;
int current = 1;
pid_t current_pid;
int curCount;
int optionalFlags = 0; 
int error = 0; 
void verbosePrint(char *argv[], int curCount, int current); 
void fileFunction(char *argv[], int flag);
void flagModifier(int option, char *argv[]); 
void sig_handler(int signum);

struct pidStorage
{
	pid_t pid;
	char** arg_start;
	int size;
};

struct pidStorage *bank;

int main(int argc, char *argv[])
{
	int opt = 0;
	int rdonly = 0;
	
	int command_arg[3];
	int command_counter = 0;
	char* all_command_values;
	
	
	int maxAlloc = 1;
	int size = 0;
	
	
	fdTable = malloc(sizeof(int) * 1000000);
	if (fdTable == NULL)
	{
		fprintf(stderr, "No space for the array of file descriptors");
		exit(1);
	}
	bank = malloc(sizeof(struct pidStorage) * 1000000);
	if (bank == NULL)
	{
		fprintf(stderr, "No space for the array of structs");
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
		{"wait", required_argument, 0, 'z'},		
		{"ignore", required_argument, 0, 'i'},
		{"default", required_argument, 0, 'd'},
		{"catch", required_argument, 0 , 't'},
		{"pipe", no_argument, 0, 'p'}, 
		 
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
	int c;			// used to iterate through command args for wait
	int fileD;
	int signum;
	
	int SIZEOFARRAY;
	  
	int fd; 
	int string_size = 0;
	
	int status;
	int exit_Value;
	struct pidStorage quack;

	while(opt != -1)
	{
		if(size == maxAlloc)
		{
			maxAlloc *= 2;
			fdTable = realloc(fdTable, maxAlloc * sizeof(char));
			bank = realloc(bank, maxAlloc * sizeof(struct pidStorage));
		}			
		
		int maxChars = 100; 
		char** commandArgs; 
		switch(opt)
		{
			case 'p':
				curCount = 1; 
				if(verboseFlag)
					verbosePrint(argv, curCount, current);  
				int temFD[2];
				if(pipe(temFD) == -1){
					fprintf(stderr, "Error: Failure to create pipes\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}
				fdTable[counter++] = temFD[0]; 
				size++; 
				if(size == maxAlloc) {
					maxAlloc *= 2;
					fdTable = realloc(fdTable, maxAlloc * sizeof(char));
				}
				fdTable[counter++] = temFD[1]; 
				current+=curCount; 
				break; 

			case 'a' :                                 //abort
				curCount = 1;
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current); 		
				}
				raise(SIGSEGV);

			case 'd' :                                //signal default
			//	printf("%s\n", argv[current + 1]);
				curCount = 1; 
				if(verboseFlag)
					verbosePrint(argv, curCount, current); 
				for(;;){
					if(argv[current+curCount] == '\0'){ 
						break; 
					}
					else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
						break; 
					curCount++; 
				}
				if(curCount != 2){ 

			}

				signum = atoi(argv[current + 1]);
				signal(signum, SIG_DFL);
				break;
		
			case 'i' :                                //signal ignore
				signum = atoi(argv[current + 1]);
				signal(signum, SIG_IGN);
				break;
				
			case 't' :		// catch
				signum = atoi(argv[current + 1]);
				signal(signum, sig_handler);
				break;
				
		
			case 'z' :
				curCount = 1;
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current);
				}
				for(i = 0; i < childCounter; i++)
				{
					current_pid = waitpid(-1, &status, 0);		
					if(WIFEXITED(status))
					{
						exit_Value = WEXITSTATUS(status);
						printf("%d ", exit_Value);
						//print out the exit value
					}
					for(z = 0; z < childCounter; z++)
					{
						if(bank[z].pid == current_pid)			// look for corresponding info in the bank
						{
							quack = bank[z];
						}
					}
					for(z = 0; z < quack.size; z++)
					{
						for(c = 0; quack.arg_start[z][c] != '\0'; c++)	// calculate the size of the argument
						{
							printf("%s", quack.arg_start[z][c]);
						}
						printf(" ");		// separate the arguments
					}
					printf("\n");
				}
				break;
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

			case 'g':                                       //pause
				curCount = 1; 
				if(verboseFlag) 
					verbosePrint(argv, curCount, current); 
				pause(); 
				break; 

			case 'u':                                        //close 
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
			int j = 0; 
			while(argv[current+1][j] != '\0') {
				if(!isdigit(argv[current+1][j])) {
					fprintf(stderr, "Error: Incorrect arguments.\n"); 
					ret = 1; 
					error = 1; 
					break; 
				}
				j++; 
			}
			if(error == 1) {
				current+=curCount; 
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				error = 0; 
				continue; 
			}
			int N = atoi(argv[current+1]); 
			if(N >= counter) {
				fprintf(stderr, "Error: File descriptor has not been opened.\n"); 
				ret = 1;
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				current+=curCount; 
				size++; 
				continue; 
			}
			int open = fcntl(fdTable[N], F_GETFL); 
			if(open < 0 || errno == EBADF) {
				fprintf(stderr, "Error: Accessing nonopen file descriptor\n"); 
				ret = 1; 
				size++; 
				current += curCount;
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				continue; 
				}
			close(fdTable[N]); 
			open = fcntl(fdTable[N], F_GETFL);
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
					verbosePrint(argv, curCount, current); 			
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
				//printf("The count is: %d\n", count); 
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
			{              
				if(!(isdigit(commandArgs[0][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.\n");
					error = 1; 
					ret = 1; 
				}
					
				
			}
			for(z = 0; z < size_of_argument2; z++)
			{						
			if(!(isdigit(commandArgs[1][z])))
				{
				fprintf(stderr, "Error in arguments. Invalid argument.\n");
					error = 1; 
					ret =1; 
				}
			}
			for(z = 0; z < size_of_argument3; z++)
			{					
			if(!(isdigit(commandArgs[2][z])))
				{
					fprintf(stderr, "Error in arguments. Invalid argument.\n");
					error = 1; 
					ret =1; 
				}
			}
			
			if (error == 1){
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				size++; 
				error = 0; 
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
				int open = fcntl(fdTable[command_arg[z]], F_GETFL); 
				if(open < 0 || errno == EBADF) {
					fprintf(stderr, "Error: Accessing nonopen file descriptor!\n"); 
					ret = 1; 
					size++; 
					current += (count+1);
					error = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					break; 
				}
			}
			if(error == 1) { 
				error = 0; 
				continue; 
			}
			size_of_argument1 = 0;
			size_of_argument2 = 0;
			size_of_argument3 = 0;		

			// MIGHT NEED TO UPDATE
			current += (count+1);

			optind+= count-1; 
		
				
			pid_t Child_PID = fork(); 
			bank[childCounter].pid = Child_PID; 			// adding values for the struct
			bank[childCounter].arg_start = &commandArgs[3];
			bank[childCounter].size = count - 3;	// factor in subtract the 3 initial args for command
			childCounter++;
				
			if (Child_PID == 0) { 
					
					for(i = 0; i < 3; i++)
					{
						fileD = command_arg[i];
						dup2(fdTable[fileD], i);
					}

					for(i = 0; i < counter; i++)
					{
						close(fdTable[i]);
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
		fdTable[counter] = fd;
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



#define _GNU_SOURCE
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>

int* fdTable;
int counter = 0;
int childCounter = 0;
int verboseFlag = 0;
int ret = 0;
int current = 1;
int curCount;
int optionalFlags = 0; 
int error = 0; 
int exit_status = 0; 
int exit_holder = 0; 
int profile = 0; 
int pipeOptions = 0; 
int waitStatus = 0; 
int optionCheck = 1; 
void verbosePrint(char *argv[], int curCount, int current); 
void fileFunction(char *argv[], int flag);
void flagModifier(int option, char *argv[]); 
void sig_handler(int signum);
int argumentNumberCheck(char *argv[]);
int argumentDigitCheck(char *argv[]); 
void exitStatusChecker(); 
void flagChecker(); 
void startingTime(struct rusage *begin, struct rusage *child_begin);
void endingTime(struct rusage *end, struct rusage *child_end);
void waitStartingTime(struct rusage *child_begin); 
void waitEndingTime(struct rusage *child_end); 
void printTimes();
void waitPrintTimes();

struct pidStorage
{
	pid_t pid;
	char** arg_start;
	int size;
};

struct pidStorage *bank;

struct rusage begin;
struct rusage end;

struct rusage child_begin;
struct rusage child_end;

struct timeval ub_time;
struct timeval sb_time;
struct timeval ue_time;
struct timeval se_time;

struct timeval ub_child_time;
struct timeval sb_child_time;
struct timeval ue_child_time;
struct timeval se_child_time;



int start1;
int start2;
int finish1;
int finish2;
int total1;
int total2;
int child_finish1;
int child_finish2;
int child_start1;
int child_start2;



int main(int argc, char *argv[])
{
	int opt = 0;
	int rdonly = 0;
	
	int command_arg[3];
	int command_counter = 0;
	
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
		{"nonblock", no_argument, 0, flag8}, ///this one for design problem 
		{"command", required_argument, 0, 'c'},
		{"directory", no_argument, 0, flag4},
		{"excl", no_argument, 0, flag6},
		{"rdwr", required_argument, 0, 'f'},
		{"cloexec", no_argument, 0, flag2}, /////this one for design problem
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
		{"wait", no_argument, 0, 'z'},		
		{"ignore", required_argument, 0, 'i'},
		{"default", required_argument, 0, 'd'},
		{"catch", required_argument, 0 , 't'},
		{"pipe", no_argument, 0, 'p'}, 
		{"profile", no_argument, 0, 'o'},
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
	int a;
	int fileD;
	int signum;
	
	int SIZEOFARRAY;
	  
	int fd; 
	int string_size = 0;
	
	int status;
	int exit_Value;

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
			case 'o':
				startingTime(&begin, &child_begin); 
				profile = 1; 
				curCount = 1; 
				if(argumentNumberCheck(argv) != 1){
					fprintf(stderr, "Error: Profile does not take arguments\n"); 
				}
		
				if(verboseFlag)
					verbosePrint(argv, curCount, current);
				current += curCount; 
				break; 
			case 'p':                                     //pipes 
				curCount = 1; 
				argumentNumberCheck(argv);

				if(verboseFlag)
					verbosePrint(argv, curCount, current);  

				if(curCount != 1){
					fprintf(stderr, "Error: Pipe takes no arguments\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}

				int temFD[2];
				if(optionalFlags !=0)
					flagChecker(); 
				exit_holder = pipe2(temFD, optionalFlags);
				optionalFlags = 0;  
				exitStatusChecker(); 
				if(exit_holder == -1){
					fprintf(stderr, "Error: Failure to create pipes\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					endingTime(&end, &child_end); 
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
				endingTime(&end, &child_end); 
				break; 

			case 'a' :                                 //abort
				startingTime(&begin, &child_begin); 
				curCount = 1;
				argumentNumberCheck(argv);
				
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current); 		
				}
				if(curCount != 1){
					fprintf(stderr, "Error: Abort takes no arguments\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					endingTime(&end, &child_end); 
					continue; 
				}
				exit_holder = raise(SIGSEGV);
				exitStatusChecker(); 
				endingTime(&end, &child_end); 
				break; 

			case 'd' :                                //signal default
				startingTime(&begin, &child_begin); 
				curCount = 1; 
				argumentNumberCheck(argv);
				if(verboseFlag)
					verbosePrint(argv, curCount, current); 
				if(curCount != 2 || argumentDigitCheck(argv) == 0){ 
					fprintf(stderr, "Error: Incorrent Argument Syntax\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount;
					continue; 
				}

				signum = atoi(argv[current + 1]);
				if(signum > 65) {
					fprintf(stderr, "Error: Incorrent Argument Syntax\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}
				signal(signum, SIG_DFL); 
				exit_holder = signum; 
				exitStatusChecker();
				current+=curCount;
				endingTime(&end, &child_end); 
				break;
		
			case 'i' :                                //signal ignore
				startingTime(&begin, &child_begin); 
				curCount = 1;
				argumentNumberCheck(argv);
				if(curCount != 2 || argumentDigitCheck(argv) == 0){ 
					fprintf(stderr, "Error: N is beyond range of signals\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}

				if(verboseFlag) 
					verbosePrint(argv, curCount, current); 

				signum = atoi(argv[current + 1]);
				if(signum > 65) {
					fprintf(stderr, "Error: N is beyond range of signals\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}
				signal(signum, SIG_IGN);
				exit_holder = signum; 
				exitStatusChecker();
				current+=curCount; 
				endingTime(&end, &child_end); 
				break;
				
			case 't' :		// catch
				startingTime(&begin, &child_begin); 
				curCount = 1; 
				argumentNumberCheck(argv);
				if(curCount != 2 || argumentDigitCheck(argv) == 0){ 
					fprintf(stderr, "Error: N is beyond range of signals\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}
				if(verboseFlag)
					verbosePrint(argv, curCount, current); 

				signum = atoi(argv[current + 1]);
				if(signum > 65) {
					fprintf(stderr, "Error: Incorrent Argument Syntax\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					continue; 
				}
				signal(signum, sig_handler); 
				exit_holder = signum; 
				exitStatusChecker();
				current +=curCount;
				endingTime(&end, &child_end); 
				break;
				
			case 'z' : {    
				startingTime(&begin, &child_end);                        //wait  
				for(i = 0; i < counter; i++)        //not sure where to put exit status here
					{
						close(fdTable[i]);
					}
				curCount = 1;
				waitStatus = 1; 
				argumentNumberCheck(argv); 
				if(curCount != 1) {
					fprintf(stderr, "Error: Wait does not take arguments\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount; 
					endingTime(&end, &child_end); 
					continue; 
				}
				
				if(verboseFlag)
				{
					verbosePrint(argv, curCount, current);
				}
				for(z = 0; z < childCounter; z++)
				{
					waitpid(bank[z].pid, &status, 0);
					if(WIFEXITED(status))
					{
						int ret_val = WEXITSTATUS(status);
						if (ret < ret_val) {
							ret = ret_val;
						}
						printf("%d ", ret);
						//print out the exit value
					}
					else if (WIFSIGNALED(status))
					{
						int sig_num = WTERMSIG(status);
						if (ret == 0)
						{
							ret = 1;
						}
						
						raise(sig_num);
						printf("%d ", ret);
					}
					for(a = 0; a < bank[z].size; a++)
					{
						for(c = 0; bank[z].arg_start[a][c] != '\0'; c++)	// calculate the size of the argument
						{
							printf("%c", bank[z].arg_start[a][c]);
						}
						if(a != bank[z].size-1)
						{
							printf(" ");
						}	
					}
					printf("\n");
				}	
				current+=curCount;
				endingTime(&end, &child_end); 
				break;
			}
			case 'r' :
				if(optionCheck == 1){
					startingTime(&begin, &child_begin); 
				}
				fileFunction(argv, O_RDONLY);
				endingTime(&end, &child_end);
				optionCheck = 1; 
				break;
			
			case 'w' :
				if(optionCheck == 1) {
					startingTime(&begin, &child_begin); 
				}
				fileFunction(argv, O_WRONLY); 
				endingTime(&end, &child_end);
				optionCheck = 1; 
				break;

			case 'f':
				if(optionCheck == 1) {
					startingTime(&begin, &child_begin); 
				}
				fileFunction(argv, O_RDWR); 
				endingTime(&end, &child_end);
				optionCheck = 1;
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
				startingTime(&begin, &child_begin); 
				curCount = 1; 
				argumentNumberCheck(argv);
				
				if(curCount != 1) {
					fprintf(stderr, "Error: Pause does not take an argument\n"); 
					ret = 1; 
					opt = getopt_long(argc, argv, "a", long_options, &option_index);
					current+=curCount;
					endingTime(&end, &child_end); 
					continue; 
				}
				if(verboseFlag) 
					verbosePrint(argv, curCount, current); 
				exit_holder = pause(); 
				exitStatusChecker(); 
				current+=curCount;
				endingTime(&end, &child_end); 
				break; 

			case 'u':                                        //close 
			startingTime(&begin, &child_begin); 
			curCount = 1; 
			argumentNumberCheck(argv);
			
			if(verboseFlag)
				verbosePrint(argv, curCount, current); 
			
			if(curCount != 2 || argumentDigitCheck(argv) == 0){ 
				fprintf(stderr, "Error: Incorrent Argument Syntax\n"); 
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				current+=curCount;
				endingTime(&end, &child_end);
				continue; 
			}
			int N = atoi(argv[current+1]); 
			if(N >= counter) {
				fprintf(stderr, "Error: File descriptor has not been opened.\n"); 
				ret = 1;
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				current+=curCount; 
				size++; 
				endingTime(&end, &child_end);
				continue; 
			}
			int open = fcntl(fdTable[N], F_GETFL); 
			if(open < 0 || errno == EBADF) {
				fprintf(stderr, "Error: Accessing nonopen file descriptor\n"); 
				ret = 1; 
				size++; 
				current += curCount;
				opt = getopt_long(argc, argv, "a", long_options, &option_index);
				endingTime(&end, &child_end);
				continue; 
				}
			exit_holder = close(fdTable[N]); 
			exitStatusChecker(); 
			//open = fcntl(fdTable[N], F_GETFL);
			//current+=2; 
			current += curCount; 
			//counter++; 
			endingTime(&end, &child_end);
			break;

			case 'v' :                               //verbose
				startingTime(&begin, &child_begin); 
				curCount = 1; 
				argumentNumberCheck(argv);
		
				if(verboseFlag)
				{			
					verbosePrint(argv, curCount, current); 			
				}
				if(curCount != 1){         //if verbose has arguments, should it still beset?
					fprintf(stderr, "Incorrect number of arguments\n"); 
					ret =1; 
				}
				verboseFlag = 1;
				current+=curCount;
				endingTime(&end, &child_end);
				break;
				
			case 'c' : 

			startingTime(&begin, &child_begin); 
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
				endingTime(&end, &child_end);
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
				endingTime(&end, &child_end);
				continue;
			}
			
			command_arg[0] = atoi(commandArgs[0]);
			command_arg[1] = atoi(commandArgs[1]);
			command_arg[2] = atoi(commandArgs[2]);

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
				endingTime(&end, &child_end);
				continue; 
			}
			size_of_argument1 = 0;
			size_of_argument2 = 0;
			size_of_argument3 = 0;		

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
			endingTime(&end, &child_end);
			break;
		}
		size++;
		
		opt = getopt_long(argc, argv, "a", long_options, &option_index);
	}
	free(bank); 
	free(fdTable); 

	exit(exit_status);
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
	int fd = open(optarg, flag, 0644);
	optionalFlags = 0; 
	if(fd == -1)
	{
		fprintf(stderr, "Error in opening file.\n");
		if(exit_status == 0)
			exit_status = fd; 
	}
	else
	{
		fdTable[counter] = fd;
	}
	current +=curCount;
	counter++;

}

void flagModifier(int option, char *argv[]) { 
	if(optionCheck == 1) {
		startingTime(&begin, &child_begin); 
		optionCheck = 0; 
	}
	if(verboseFlag) {
		verbosePrint(argv, curCount, current); 
	}
	optionalFlags |= option; 
	current++; 
}

void sig_handler(int signum)
{
	fprintf(stderr, "Caught signal: %d\n", signum);
	exit(signum);
}

int argumentNumberCheck(char *argv[]) {
	for(;;){
		if(argv[current+curCount] == '\0'){ 
			break; 
		}
		else if(argv[current+curCount][0] == '-' &&argv[current+curCount][1] == '-' )
			break; 
		curCount++; 
	}
	return curCount; 
}

int argumentDigitCheck(char *argv[]) {
	int j = 0; 
	while(argv[current+1][j] != '\0') {
		if(!isdigit(argv[current+1][j])) {
			return 0; 
		}
		j++; 
	}
	return 1; 
}

void exitStatusChecker() {
	if(exit_holder > exit_status)
		exit_status = exit_holder; 
}

void flagChecker() { 
	switch(optionalFlags) {
		case O_NONBLOCK:
			break; 
		case O_CLOEXEC:
			break;
		case O_CLOEXEC | O_NONBLOCK:
			break; 
		default:
			fprintf(stderr, "Error: Incorrect options passed to pipe\n"); 
			optionalFlags = 0; 
			break; 
	}
}

void startingTime(struct rusage *begin, struct rusage *child_begin) {
	if(profile == 1){
		if(waitStatus == 1) {
			waitStartingTime(child_begin); 
		}
		else {
			getrusage(RUSAGE_SELF, begin);
			ub_time = begin->ru_utime;
			sb_time = begin->ru_stime;
			start1 = ((int64_t)ub_time.tv_sec * 1000000) + ub_time.tv_usec;
			start2 = ((int64_t)sb_time.tv_sec * 1000000) + sb_time.tv_usec;
		}
	}
}
void waitStartingTime(struct rusage *child_begin){
	getrusage(RUSAGE_CHILDREN, child_begin);
	ub_child_time = child_begin->ru_utime;
	sb_child_time = child_begin->ru_stime;
	child_start1 = ((int64_t)ub_child_time.tv_sec * 1000000) + ub_child_time.tv_usec;
	child_start2 = ((int64_t)sb_child_time.tv_sec * 1000000) + sb_child_time.tv_usec;
}

void endingTime(struct rusage *end, struct rusage *child_end) { 
	if(profile == 1) {
		if(waitStatus == 1) {
			waitEndingTime(child_end); 
			waitPrintTimes(); 
		}
		else {
			getrusage(RUSAGE_SELF, end);
			ue_time = end->ru_utime;
			se_time = end->ru_stime;
			finish1 = ((int64_t)ue_time.tv_sec * 1000000) + ue_time.tv_usec;
			finish2 = ((int64_t)se_time.tv_sec * 1000000) + se_time.tv_usec;
			printTimes(); 
		}
		
	}
}

void waitEndingTime(struct rusage *child_end) {
	getrusage(RUSAGE_SELF, child_end);
	ue_child_time = child_end->ru_utime;
	se_child_time = child_end->ru_stime;
	child_finish1 = ((int64_t)ue_child_time.tv_sec * 1000000) + ue_child_time.tv_usec;
	child_finish2 = ((int64_t)se_child_time.tv_sec * 1000000) + se_child_time.tv_usec;
}

void printTimes() {	
	printf("finish1 is: %d\n", finish1); 
	printf("finish2 is: %d\n", finish2);
	printf("start1 is: %d\n", start1);
	printf("start2 is: %d\n", start2);

	total1 = finish1 - start1;
	total2 = finish2 - start2;
	printf("the User time is: %d\n", total1);
	printf("the System time is: %d\n", total2);
}

void waitPrintTimes() {
	printf("finish1 is: %d\n", child_finish1); 
	printf("finish2 is: %d\n", child_finish2);
	printf("start1 is: %d\n", child_start1);
	printf("start2 is: %d\n", child_start2);

	total1 = child_finish1-child_start1; 
	total2 = child_finish2 - child_start2; 
	printf("the User time is: %d\n", total1); 
	printf("the System time is: %d\n", total2); 
}
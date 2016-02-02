# SimpleShell
CS 111 Lab 1

Person A: Zachary Bordofsky, UID: 304443257
Person B: Christopher Zhu, UID: 104455996

Currently the limitaions are that it only can handle the commands: --rdonly, --wronly, --verbose, and --command. 
It is able to handle situations in which case the user provides false arguments or an incorrect number of arguments. 
It also prints out error messages whenever something fails to execute but still continues onto the next option. 
The SIMPleton Shell is a simple stripped down shell that does not use a scripting language and we do not interact with it at a 
terminal. We instead call simpsh command which acts like a shell instead. As of this version, we have not yet created pipes yet as 
that will be implemented in Part 1b. It also handles exit statuses as they exit in a simple form since we have not implemented 
the wait command yet. Our invocations for simpsh uses standard shell syntax because it comes from the standard shell. 
We believe that this can handle cases because we have implemented many test cases.

Lab B.
The current limitations on the code is now that it cannot run the the --profile command. All other commands listed on the spec are 
working up to the descriptions listed. All of the error handling is also in place so that if any commands are listed without the 
proper number of arguments, or strings that should be numbers will give an error. This error will not stop the running, the SIMPleton 
Shell will instead move on to the next command, but it will print an error statement, and change the exit status. These exit statuses 
can be seen in the --wait command as they occur. 

Lab B Design Problem 1:
The --pipe command has been updated to be able to have flags applied to the file descriptors created by pipe(). The man page for pipe 
says that the function pipe2(int pipefd[2], int flags) has the second parameter flags which can be used to add options onto the pipe.
This function works for the normal cases becasue if the value of flags is zero, then pipe2 behaves exactly like pipe. This allows us
to apply some flags to pipes. According to the man page, flags that can be added to pipe are nonblock and cloexec. If any other value
is ORed into the flags variable, then the pipe2 call will return an error. For this reason, we implemented our own error checking to
prevent a failure. Once we OR all the values into the flags variable, right before calling pipe2, we check the value of the flags 
variable to see if it is zero, CLOEXEC, NONBLOCK, or CLOEXEC and NONBLOCK ORed together. If the value is different than any of these, 
then an error message will be printed, and flags will be set to 0, and then passed to pipe2. So either the user can use the right 
flags, or no flags will work with pipe.
NOTE: at the submission of this, the --profile option is in the process of being implemented, but is not complete yet. All code for 
it has been commented out, and should have no effect on the running of any other command. 
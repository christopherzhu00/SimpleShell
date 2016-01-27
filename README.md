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

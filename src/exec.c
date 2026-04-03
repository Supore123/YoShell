#include <sys/wait.h>
#include "shell.h"

int execute_args(char** args)
{
	pid_t pid;
	int status;

	if(args[0] == NULL)
	{
		// empty statement
		return 1;
	}

	pid = fork();
	if(pid == 0)
	{
		// Child
		if(execvp(args[0], args) == -1)
		{
			perror("yoshell");
		}
		exit(EXIT_FAILURE);

	}
	else if(pid<0)
	{
		// Fork Error
		perror("yoshell");
	}
	else
	{
		// Parent
		do 
		{
 	           waitpid(pid, &status, WUNTRACED);
        	}while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}

#include "shell.h"

void run_shell_loop(void) 
{
    char *line;
    char **args;
    int status = 1;

    do
    {
        printf("yoshell> ");

        line = read_line(); 		// Get the string
        args = read_args(line); 	// Break into parsing 
        status =  execute_args(args); 	// Execute command

        free(line);
        free(args);
    }while(status);
}


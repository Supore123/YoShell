#include "shell.h"

void run_shell_loop(void) 
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("yoshell> ");
        line = read_line();
        args = read_args();
        status =  execute_args();       

        free(line);
        free(args);
    }while(status);
}

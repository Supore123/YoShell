#include "shell.h"

void run_shell_loop(void) 
{
    char *line;
    //char **args;
    int status = 1;

    do
    {
        printf("yoshell> ");

        line = read_line(); 		// Get the string
        args = read_args(); 		// Break into parsing 
//       status =  execute_args(); 	// Execute command

	// Temp test
	printf("%s", line);
        free(line);
        free(args);
    }while(status);
}

char *read_line(void)
{
 char *line = NULL;
 size_t bufsize = 0;

 if (getline(&line, &bufsize, stdin) == -1)
 {
	// Check if we meet EOL
	if(feof(stdin))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	else
 	{
		free(line); /* avoid memory leaks when getline fails */
		perror("error while reading the line from stdin");
   		exit(EXIT_FAILURE);
  	}
 }
 return (line);
}

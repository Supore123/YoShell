#include "shell.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

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
//       status =  execute_args(); 	// Execute command

	for (int i = 0; args[i] != NULL; i++) 
	{
            printf("Arg[%d]: %s\n", i, args[i]);
        }

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

char **read_args(char *line) 
{
    int bufsize = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) 
    {
        fprintf(stderr, "yoshell: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // strtok returns a pointer to the first "token" (word) it finds
    token = strtok(line, TOK_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        // If we run out of space in our array, reallocate more
        if (position >= bufsize) 
	{
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) 
	    {
                fprintf(stderr, "yoshell: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        // Subsequent calls to strtok must use NULL as the first argument
        token = strtok(NULL, TOK_DELIM);
    }
    
    // The "NULL-terminated" requirement for execvp
    tokens[position] = NULL;
    return tokens;
}

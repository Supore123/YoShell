#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

int execute_args(char** args)
{
	if(args[0] == NULL)
	{
		// empty statement
		return 1;
	}
	
	for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

	return launch_process(args);
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


int launch_process(char **args)
{
	int status;
	pid_t pid;

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

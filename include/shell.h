#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function Defines
void run_shell_loop(void);
char *read_line(void);
char **read_args(char *line);
int execute_args(char **args);
int launch_process(char **args); // New helper for external commands

// Path Envs
char *resolve_path(char *command);

// Custom built in shell handlers
int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int num_builtins();

// Declarations to make arrays visible across files
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif

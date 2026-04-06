#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

// ANSI Color Codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BOLD    "\x1b[1m"

// Function Defines
void run_shell_loop(void);
char *read_line(void);
char **read_args(char *line);
int execute_args(char **args);
int launch_process(char **args); // New helper for external commands

// Custom built in shell handlers
int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int num_builtins();

// Declarations to make arrays visible across files
extern char *builtin_str[];
extern int (*builtin_func[]) (char **);

#endif

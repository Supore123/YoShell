#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // For ssize_t

// Function prototypes
void run_shell_loop(void);
char *read_line(void);

#endif

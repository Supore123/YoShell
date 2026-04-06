#include "shell.h"

void run_shell_loop(void) 
{
    char *line;
    char **args;
    int status = 0;         // 0 means success in Unix. We start with a "success" state.
    int keep_running = 1;   // Replaces `status` as the loop control variable

    do
    {
        char cwd[PATH_MAX];
        
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            
            char *indicator = (status == 0) ? (COLOR_GREEN "➜" COLOR_RESET) : (COLOR_RED "✗" COLOR_RESET);
            
            // Format: [Indicator] [Path] >
            printf("%s " COLOR_BLUE "%s" COLOR_RESET " " COLOR_BOLD ">" COLOR_RESET " ", indicator, cwd);
        } else {
            // Fallback if getcwd fails
            printf(COLOR_GREEN "> " COLOR_RESET);
        }

        line = read_line();
        args = read_args(line);

        // Handle empty input explicitly so it doesn't trigger a failure indicator
        if (args[0] == NULL) {
            status = 0; 
        } 
        // Handle exit builtin directly in the REPL to break the loop cleanly
        else if (strcmp(args[0], "exit") == 0) {
            keep_running = 0;
        } 
        // Execute normal commands and capture their actual exit status
        else {
            status = execute_args(args); 
        }

        free(line);
        free(args);
        
    } while(keep_running);
}

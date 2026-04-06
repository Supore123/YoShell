#include "shell.h"
#include <limits.h>

char *resolve_path(char *command) 
{
    // If the command already includes a slash, treat it as an absolute/relative path
    if (strchr(command, '/') != NULL) {
        return strdup(command);
    }

    // Fetch the PATH environment variable
    char *path_env = getenv("PATH");
    if (path_env == NULL) {
        return strdup(command);
    }

    // Duplicate PATH because strtok modifies the string it operates on
    char *path_copy = strdup(path_env);
    if (!path_copy) {
        fprintf(stderr, "yoshell: memory allocation error\n");
        return strdup(command);
    }

    char *dir = strtok(path_copy, ":");
    char full_path[PATH_MAX];

    // Search directories in PATH for the executable
    while (dir != NULL) {
        // Construct the full path: dir/command
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

        // Check if the file exists and is executable
        if (access(full_path, X_OK) == 0) {
            free(path_copy);
            return strdup(full_path); // Found it!
        }
        
        // Move to the next directory in the PATH string
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    
    // Fallback: return the original command if not found in any PATH directory
    return strdup(command);
}

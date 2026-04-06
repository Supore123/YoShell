#include "shell.h"

int shell_cd(char **args);
int shell_exit(char **args);
int shell_help(char **args);
int shell_system(char **args);

char *builtin_str[] = {
  "cd",
  "exit",
  "help",
  "sysinfo"
};

int (*builtin_func[]) (char **) = {
  &shell_cd,
  &shell_exit,
  &shell_help,
  &shell_system
};

int num_builtins() 
{
  return sizeof(builtin_str) / sizeof(char *);
}

int shell_system(char **args)
{
    char hostname[256] = "linux";
    #ifdef __linux__
        gethostname(hostname, sizeof(hostname));
    #endif
    printf("[%s@%s] \n", getenv("USER"), hostname);
    return 1;
}

int shell_cd(char **args) 
{
  if (args[1] == NULL) 
  {
    fprintf(stderr, "yoshell: expected argument to \"cd\"\n");
  } 
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("yoshell");
    }
  }
  return 1;
}

int shell_help(char **args) 
{
  printf("YoShell: Custom YohannesShell for fun!\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (int i = 0; i < num_builtins(); i++) 
  {
    printf("  %s\n", builtin_str[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

int shell_exit(char **args) 
{
  return 0;
}

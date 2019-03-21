#include "myshell.h"

extern char **environ;

void init_shell_env() {
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  setenv("shell",cwd,1);
}

/* Function to get user input
  Takes an empty string used to store input for later parsing
  input is temporariliy stored in buffer then coppied
  to the arg *str */
int input_prompt(char *cmd_str) {
  char *buffer = (char *) malloc(MAXCHR);
  printf("my_shell> ");
  fgets(buffer, MAXCHR, stdin);
  int len = strlen(buffer);
  if (buffer[len-1] == '\n' ) {
    buffer[len-1] = 0;
  }
  if (strlen(buffer) != 0) {
    strcpy(cmd_str, buffer);
    return 0;
  } else {
    free(buffer);
    return 1;
  }
}

void quit_shell() {
  printf("\nThank you for using my_shell\n\n");
  exit(0);
}

void get_current_directory() {
  char cwd[1000];
  getcwd(cwd, sizeof(cwd));
  printf("\nCurrent_Dir: %s\n", cwd);
}

void print_dir(char *path) {
  get_current_directory();
  DIR *d;
  struct dirent *dir;

  if (path == NULL) {
    d = opendir(".");
  } else {
    d = opendir(path);
  }

  int i = 0;
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      printf("%10s ", dir->d_name);
      i++;
      if (i % 5 == 0) {
        printf("\n");
      }
    }
    closedir(d);
  }
  printf("\n");
}

void change_directory(char *path) {
  if (path == NULL) {
    get_current_directory();
  } else{
    chdir(path);
  }
}

void show_environ() {
  for (int i = 0; environ[i] != NULL; i++) {
    printf("%s\n",environ[i]);
  }
}

void echo_string(char **parsed_input) {
  parsed_input++;
  while (*parsed_input != NULL) {
    printf("%s ", *parsed_input );
    parsed_input++;
  }
  printf("\n");
}

void shell_man() {
  puts("\nList of built in commands:"
        "\n  'quit' exit the my_shell"
        "\n  'clr' clears the screen"
        "\n  'dir' list contents of current directory"
        "\n  'cd <directory path>' cd checks the current directory, or changes to the input directory path"
        "\n  'environ' list all of the curent environment varialbes"
        "\n  'echo <string>' send input string to std out"
        "\n  'help' display all valid commands accepted by my_shell"
        "\n\n my_shell also supports standard UNIX shell commands"
        "\n * output redirection and background processes are not supported"
        "\n * for more information see readme file\n");
}

int builtin_cmd_handler(char **parsed_input) {
  int num_of_cmds = 7, builtin_cmd_id = 0;
  char *list_of_builtin_cmds[num_of_cmds];

  list_of_builtin_cmds[0] = "quit";
  list_of_builtin_cmds[1] = "clr";
  list_of_builtin_cmds[2] = "cd";
  list_of_builtin_cmds[3] = "dir";
  list_of_builtin_cmds[4] = "environ";
  list_of_builtin_cmds[5] = "echo";
  list_of_builtin_cmds[6] = "help";

  for (int i = 0; i < num_of_cmds; i++) {
    if (strcmp(parsed_input[0], list_of_builtin_cmds[i]) == 0) {
      builtin_cmd_id = i + 1;
      break;
    }
  }

  switch (builtin_cmd_id) {
    case 1:
      quit_shell();
    case 2:
      clear();
      return 1;
    case 3:
      change_directory(parsed_input[1]);
      return 1;
    case 4:
      print_dir(parsed_input[1]);
      return 1;
    case 5:
      printf("Environment vars: \n");
      show_environ();
      return 1;
    case 6:
      echo_string(parsed_input);
      return 1;
    case 7:
      shell_man();
      return 1;
    default:
      // not internal cmd
      break;
  }
  return 0;
}

/* If cmd_str contains a pipe return 1 */
int parse_cmdstr_by_pipe(char *cmd_str, char **piped_cmds) {
  for (int i = 0; i < 2; i++) {
    piped_cmds[i] = strsep(&cmd_str, "|");
    if (piped_cmds[i] == NULL) {
      break;
    }

    if (piped_cmds[1] == NULL) {
      return 0;
    } else {
      return 1;
    }
  }
}

void parse_cmdstr_by_space(char *cmd_str, char **parsed_cmd_list) {
  for (int i = 0; i < MAXARGS; i++) {
    parsed_cmd_list[i] = strsep(&cmd_str, " ");
    if (parsed_cmd_list[i] == NULL) {
      break;
    }
    if (strlen(parsed_cmd_list[i]) == 0) {
      i--;
    }
  }
}

int process_input_string(char *cmd_str, char **parsed_cmds, char **piped_cmds) {
  char *str_piped[2];
  int pipe_count = 0;

  // piped_cmd_count = parse_cmdstr_by_pipe(cmd_str, str_piped);
  // printf("the ammount of pipes found is: %d\n", piped_cmd_count );

  // if (pipe_count) {
    // parse_cmdstr_by_space(str_piped[0], parsed_cmds);
    // parse_cmdstr_by_space(str_piped[1], parsed_pipe_list);
  // } else {
    parse_cmdstr_by_space(cmd_str, parsed_cmds);
  // }

  if (builtin_cmd_handler(parsed_cmds)) {
    return 0;
  } else {
    return 1 + pipe_count;
  }
}

void execute_cmd(char **parsed_cmds) {
  // create a child process
  pid_t pid = fork();

  if (pid == -1) {
    printf("\nFork faild!\n" );
    return;
  } else if (pid == 0) {
    if (execvp(parsed_cmds[0], parsed_cmds) < 0) {
      printf("\n!%s cmd was not found!\n\n", parsed_cmds[0]);
    }
    exit(0);
  } else {
    waitpid(pid, 0,0); // wait for child and reap
    return;
  }
}

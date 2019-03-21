#include <stdio.h>
#include <stdlib.h>
#include "myshell.h"

int main(int argc, char **argv) {

  init_shell_env();

  char *input_string = (char*) malloc(MAXCHR);
  char **parsed_cmds = (char**) malloc(MAXARGS);
  char **piped_cmds = (char**) malloc(MAXARGS);
  int exec_flag = 0;

  clear();
  while (1) {
    // take input
    if (input_prompt(input_string)) {
      continue;
    }

    exec_flag = process_input_string(input_string, parsed_cmds, piped_cmds);

    // execute a non built-in cmd
    if (exec_flag == 1) {
      execute_cmd(parsed_cmds);
    }
    // if (exec_flag == 2) {
    //   exec_args_piped(parsed_cmds, piped_cmds);
    // }
  }

  free(input_string);
  free(parsed_cmds);
  free(piped_cmds);
  return 0;
}

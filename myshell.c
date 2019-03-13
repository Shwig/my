
#include <stdio.h>
#include <stdlib.h>
#include "myshell.h"

int main(int argc, char **argv) {

  char input_string[MAXCHR], *parsed_args[MAXLIST];
  char* parsed_args_piped[MAXLIST];
  int exec_flag = 0;

  clear();

  // while (1) {
  //   // take input
  //   if (get_input(input_string)) {
  //     continue;
  //   }
    // // process
    // exec_flag = process_string(input_string, parsed_args, parsed_args_piped);
    // // exec_flag returns zero if there is no command
    // // or it is a builtin command,
    // // 1 if it is a simple command
    // // 2 if it is including a pipe.
    //
    // // execute
    // if (exec_flag == 1) {
    //   execArgs(parsedArgs);
    // }
    // if (exec_flag == 2) {
    //   exec_args_piped(parsed_args, parsed_args_piped);
    // }
  // }
  return 0;
}

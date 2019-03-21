#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHR 512 // maximum number of characters supported by shell input
#define MAXARGS 32 // maximum number of commands supported by shell parser

// Clear shell window using escape sequences
#define clear() printf("\033[H\033[J")

extern char **environ;

// function prototypes
int input_prompt(char *cmd_str);
void get_current_directory();
void quit_shell();
int builtin_cmd_handler(char **parsed_input);
int process_input_string(char *cmd_str, char **parsed_cmds, char **piped_cmds);
void parse_cmdstr_by_space(char *cmd_str, char **parsed_cmds);
int parse_cmdstr_by_pipe(char *cmd_str, char **piped_cmds);
void print_dir(char *path);
void change_directory(char *path);
void show_environ();
void echo_string(char **parsed_input);
void init_shell_env();
void shell_man();
void execute_cmd(char **parsed_cmds);

#endif

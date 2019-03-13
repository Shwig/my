#ifndef MYSHELL_H
#define MYSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXCHR 1000 // maximum number of characters supported by shell input
#define MAXLIST 100 // maximum number of commands supported by shell parser

// Clear shell window using escape sequences
#define clear() printf("\033[H\033[J")

// function prototypes
int get_input(char *str);

#endif

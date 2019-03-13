#include "myshell.h"

/* Function to get user input
  the value taken from the user is coppied from the buffer
  to the */
int get_input(char *str) {
  char *buffer;
  fgets(buffer, MAXCHR, stdin);
  if (strlen(buffer) != 0) {
    strcpy(str, buffer);
    return 0;
  } else {
    return 1;
  }
}

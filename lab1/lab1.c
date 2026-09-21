#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  printf("Please enter some text: ");

  char *buff = NULL;
  size_t size = 0;

  if (getline(&buff, &size, stdin) != 1L) {
    // assign the return value of getline into this
    char *input_str = buff;
    char *delim = "\t\n\r ";
    char *token = NULL;
    char *saveptr = NULL;
    printf("Tokens: \n");
    while ((token = strtok_r(input_str, delim, &saveptr))) {
      printf("  %s\n", token);
      input_str = NULL;
    }
  } else {
    printf("Getline fail. \n");
  }
  free(buff);
  return 0;
}

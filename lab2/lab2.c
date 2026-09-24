#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>

int main() {
  char *buff = NULL;
  size_t size = 0;
  ssize_t num_read;

  num_read = getline(&buff, &size, stdin);

  printf("you typed: %s\n", buff);

  free(buff);
  return 0;
}

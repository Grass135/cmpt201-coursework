#define _POSIX_C_SOURCE 200809
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *message = "CTRL-C Pressed\n";

void singalHanlder(int signum) {
  write(STDOUT_FILENO, message, strlen(message));
  // printf("%s", message); // Don't user; not signal safe
}

int main() {
  struct sigaction act;
  act.sa_handler = signalHandler; // signal handler function
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  // Register signal handler
  int ret = sigaction(SIGINT, &act, NULL);
  if (ret == -1) {
    perror("Sigaction() failed");
    exit(EXIT_FAILURE);
  }

  while (true)
    sleep(1);
}

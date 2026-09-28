#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (true) {
    printf("Enter programs to run.\n");
    printf("> ");

    // Read user command
    char *line = NULL;
    size_t len = 0;
    if ((len = getline(&line, &len, stdin)) != -1) {

      // Strip linefeed
      line[len - 1] = '\0';

      // Run the command
      pid_t pid = fork();
      // PARENT
      if (pid != 0) {

        // Parent wait
        int wstatus = 0;
        pid_t wpid = waitpid(pid, &wstatus, 0);
        if (wpid == -1) {
          perror("waitpid");
          exit(EXIT_FAILURE);
        }

        // Child exec
      } else if (pid == 0) {

          if (execl(line, line, NULL) == -1) {
            perror("execl");
            exit(EXIT_FAILURE);
          }
      } else {
        printf("Getline failled\n");
        exit(EXIT_FAILURE);
      }
    }
    free(line);
  }
}

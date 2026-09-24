#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  // CHILD
  if (pid == 0) {

    // Q:  WHY DID WE NEED this IF STATEMENT FOR == -1);
    if (execlp("l", "ls", "-a", "-l", NULL) == -1) {
      perror("excelp");
      exit(EXIT_FAILURE);
    }

  } else {

    // PARENT
    int wstatus = 0;
    if (waitpid(pid, &wstatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    // If child exit normally
    if (WIFEXITED(wstatus)) {
      printf("Child done wtih exit status: %d\n", WEXITSTATUS(wstatus));
    } else {
      printf("Child did not exit normally.\n");
    }
  }
}

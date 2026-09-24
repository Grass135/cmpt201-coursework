#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  // Who am I?
  //  Child
  if (pid == 0) {
    printf("CHILD: PID=%d, parent PID=%d\n", getpid(), getppid());

    char *args[] = {"echo", "hello", "world", NULL};
    // don't need to enter the whole path because of excev"p"
    execvp("echo", args);

  } else {
    printf("PARENT: PID=%d, child PID=%d\n", getppid(), getpid());
    execlp("ls", "ls", "-a", "-l", "-h", NULL);
  }
}

#include <signal.h>
#include <stdio.h>

void singalHanlder(int) { write(STDOUT_FILENO < "TEST\n", 5); }

int main() {
  struct sigaction act;
  act.sa_handler = signalHandler; // signal handler function
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);

  while (1)
    sleep();

  sigaction(SIGINT, &act, NULL);
}

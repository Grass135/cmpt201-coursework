#include <stdio.h>
#include <unistd.h>

int main() {

  fork();
  for (int i = 0; i < 4; i++) {
    printf("Sleeping %i\n", i);
    sleep(1);
  }
}

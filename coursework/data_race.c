#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int cnt = 0;

void *add_10_millions_time(void *args) {
  int i = 0;
  while (i < 1000000) {
    cnt++;
    i++;
  }
  return NULL;
}

int main() {
  pthread_t id1, id2;
  if (pthread_create(&id1, NULL, add_10_millions_time, NULL) != 0) {
    perror("Unable to create thread.");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&id2, NULL, add_10_millions_time, NULL) != 0) {
    perror("Unable to create thread.");
    exit(EXIT_FAILURE);
  }
  void *thread_ret = 0;
  if (pthread_join(id1, &thread_ret) != 0) {
    perror("Unable to join");
    exit(EXIT_FAILURE);
  }
  if (pthread_join(id2, &thread_ret) != 0) {
    perror("Unable to join");
    exit(EXIT_FAILURE);
  }
  printf("cnt is: %i\n", cnt);

  printf("DONE\n");
}

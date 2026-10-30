#define _GNU_SOURCE
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void *print(void *arg) {
  char *text = arg;
  printf("In thread %d: %s\n", gettid(), text);
  // Print out argumnet and its own ID with gettid()
  sleep(1);
  printf("THreads done!\n");
  return (void *)strlen(text);
}

int main(void) {

  pthread_t thread_id;
  // int result = pthread_create(&thread_id, NULL, print("HI"), ret_val);
  if (pthread_create(&thread_id, NULL, print, "Hello:D") != 0) {
    perror("Unable to create thread.");
    exit(EXIT_FAILURE);
  }
  // this a region memory that will hold an andress
  void *ret_val = 0;
  if (pthread_join(thread_id, &ret_val) != 0) {
    perror("Unable to join");
    exit(EXIT_FAILURE);
  }

  printf("Thread return %lu\n", (uint64_t)ret_val);

  printf("DONE\n");
}

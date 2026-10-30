
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Lock 1 and 2
pthread_mutex_t mutex0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


static void *func(void *arg) {
  pthread_mutex_lock(&mutex);
  printf("Hello\n");
  pthread_exit(0);
  pthread_mutex_unlock(&mutex);
}

int main(int argc, char *argv[]) {
  pthread_t t1, t2;

  pthread_create(&t1, NULL, func, NULL);

  pthread_create(&t2, NULL, func, NULL);

  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
}

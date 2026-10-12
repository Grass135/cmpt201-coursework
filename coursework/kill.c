#define _PPSIX_C_SOURCE 200809
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

static char *message = "CTRL-C Pressed\n";
void handle_sigint(int signum){
  write(STDOUT_FILENO, message, strlen(message));
}

int main(){
  

  pid_t pid = fork(); 

  if(pid == -1){
    struct sigaction act;
    act.sa_handler = handle_sigint;
    act.sa.falgs = 0;
    sigemptyset(&act.sa_mask);

 

  }

  //CHILD PROCESS
  else if(pid == 0){

    while(1){
      sleep(1);
    }

  }
}

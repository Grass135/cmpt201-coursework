#define _POSIX_C_SOURCE 200809L
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LEN 5

char *input_history[MAX_LEN];
int history_count = 0;

void add_to_history(char *input);
void remove_oldest_record();
void print_history();
char *get_input();


int main(){
    while (true) {

    //Get user input
        char *input = get_input();
        add_to_history(input);
        if(strcmp(input, "print") == 0) {
          print_history();
        }
    }  
    for(int i = 0; i < MAX_LEN; i++){
        free(input_history[i]);
    }

    return 0;
}
    
char *get_input(){
    char *buffer = NULL;
    size_t buffsize = 0;
    printf("Enter input: ");
    size_t len = getline(&buffer, &buffsize, stdin);
    if (len == -1){
        exit(1);
    }
    // Remove the newline character at the end of the inpit
    buffer[len-1] = '\0';
    return buffer;
}

void add_to_history(char *input){
    if (history_count >= MAX_LEN){
        remove_oldest_record();
    }
    input_history[history_count] = input;
    history_count++;
}

void remove_oldest_record(){
    if (history_count > 0) {
        // Free the memory of the oldest record
        free(input_history[0]);
    
      for(int i = 1; i < history_count; i++){
        input_history[i-1] = input_history[i];  
      }
      history_count--;
    }
} 

void print_history(){
    for (int i = 0; i < history_count; i++){
        printf("%s\n", input_history[i]);
    }
}

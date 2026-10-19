#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *next;
};

// pointer to my list
void append(struct Node **pList, int data) {
  // Make new node
  // size of -> tell how many bytes in that newNode
  // malloc allocate memory for the node
  struct Node *newNode = malloc(sizeof(*newNode));
  if (newNode == NULL) {
    perror("Malloc failed.");
    exit(EXIT_FAILURE);
  }

  newNode->data = data;
  newNode->next = NULL;

  // Link into list
  if (*pList == NULL) {
    // Make this the first element
    *pList = newNode;
  } else {
    // Find the end
    struct Node *current = *pList;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

void freeList(struct Node **pList) {
  struct Node *current = *pList;
  while (current != NULL) {
    struct Node *next = current->next;
    free(current);
    current = next;
  }
  *pList = NULL;
}

void printList(struct Node *list) {
  printf("The list is: ");
  struct Node *current = list;
  while (current != NULL) {
    printf("%d, ", current->data);
    current = current->next;
  }
  printf("\n");
}
int main() {
  printf("C Linked List Demo\n");

  // Create a linked list (head)
  struct Node *head = NULL;

  // Insert some data
  append(&head, 10);
  append(&head, 20);
  append(&head, 30);
  append(&head, 40);
  // Print list
  // Don't need to change it so don't need the address)
  printList(head);
  // Free memory
  freeList(&head);
}

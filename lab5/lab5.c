#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  while (current != NULL) {
    // If we find the first block that have bigger size than required
    // We return the id of the block right away
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  // If we do not find any block fit -> return -1
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;

  // We iterate through the linked list
  // if we find a block that is big enough, we save the id -> a node
  // update the id if we the new size we found is smaller than
  // the one we found before
  struct header *current = free_list_ptr;
  struct header *update_node = NULL;

  while (current != NULL) {
    if (current->size >= size) {
      // update the size if found better fit size
      if (update_node == NULL || update_node->size >= current->size) {
        update_node = current;
      }
    }
    // Move on to next node if don't fit
    current = current->next;
  }
  // we did not find any size that fit or
  // update_node did not get update
  if (update_node == NULL) {
    return best_fit_id;
  } else {
    return update_node->id;
  }
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  // This is similar to best fit but we look for the largest size
  struct header *current = free_list_ptr;
  struct header *update_node = NULL;

  while (current != NULL) {
    if (current->size >= size) {
      // update the size if found bigger size
      // if the current size is bigger than saved size -> update it
      if (update_node == NULL || update_node->size <= current->size) {
        update_node = current;
      }
    }
    // Move on to next node if don't fit
    current = current->next;
  }
  if (update_node == NULL) {
    return worst_fit_id;
  } else {
    return update_node->id;
  }
}

// Free memory
void free_memory(struct header **list) {
  struct header *current = *list;
  while (current != NULL) {
    struct header *next = current->next;
    free(current);
    current = next;
  }
  *list = NULL;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %i\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %i\n", best_fit_id);
  printf("The ID for Worst-fit algorithm is: %i\n", worst_fit_id);

  // Free memory
  free_memory(&free_list_ptr);
  return 0;
}

// TASK 2: Coalescing Contiguous Free Blocks
/* z is the newly free block
 * Go through the free block list
 * - If we have the any address of a block end on the
 * beginning address of z block 
 * (for example m+m->size == address of z
 * -> we merge them by adding the m->size = m-size + z->size to merge them together
 *  We update the m->next to z->next
 * - if the beginning address of a block end on the end of
 *   newly free block
 *   (for example address of n == z + z->size)
 * -> we merge them by adding the z->size = n->size + z->size
 * we update the z->next to n->next

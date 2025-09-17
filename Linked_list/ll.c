#include "ll.h"

// clang-format off
list_t *create_list(void) {
  list_t *new_list = (list_t *)malloc(sizeof(list_t));
  if (new_list == NULL)
    return NULL;

  new_list->tail = NULL;
  new_list->head = NULL;
  return new_list;
}

int list_push(list_t *list, int data) {
  if (list == NULL) {
    return -1;
  }

  // If this condition is true, the list just got created
  if (list->head == NULL && list->tail == NULL) {
    list->tail = new_node(data);
    if (list->tail == NULL)
      return FAILED_PUSH; // Failed to push the first element on the list

    list->head = list->tail;
    list->list_size++;
    return SUCCESS_PUSH;
  }

  node_t *next_node = new_node(data); 
  if (next_node == NULL)
    return FAILED_PUSH;

  next_node->previous = list->head;
  list->head->next = next_node;
  list->head = next_node;
  list->list_size++;
  return SUCCESS_PUSH;
}

node_t *new_node(int data) {
  node_t *node = (node_t *) malloc(sizeof(node_t));
  if (node == NULL) {
    return NULL;
  }

  node->data = data;
  node->next = NULL;
  node->previous = NULL;

  return node;
}

int list_pop(list_t *list) {
  if (list == NULL)
    return FAIL_POP;
  
  node_t *old_head = list->head;

  list->head = old_head->previous;
  list->head->next = NULL;
  free(old_head);
  
  list->list_size--;
  return SUCCESS_POP;
}

int list_destroy(list_t *list) {
  if (list == NULL)
    return FAILED_DESTROY;
  
  node_t *current_node = list->tail;
  node_t *next_node = NULL;
  while (current_node != NULL) {
    next_node = current_node->next;
    free(current_node);
    current_node = next_node;
  }
  
  free(list);
  return SUCCESS_DESTROY;
}


int list_remove(list_t *list, int data) {
  if (list == NULL || (list->head == NULL && list->tail == NULL))
    return FAIL_REMOVE;

  node_t *current_node = list->tail;
  while (current_node != NULL) {
    if (current_node->data == data) {

      /* If the node is not the only one in the list, then we'll check the 3 possiblities.
          1 - The current node is the head
          2 - The current node is the tail
          3 - The current node is somewhere else on the list

        For the possiblity possiblity we will do.
          1 - Change the head to the previous node and set to NULL the "next pointer" of the new head, this will avoid a dangling pointer reference
          2 - Change the tail to the next node and set to NULL the "previous pointer" of the new tail, also avoiding dangling pointer.
          3 - Just link the "next pointer" of the previous node to the "next pointer" of the current node, and link the "previous pointer" of the next node to the "previous"
              pointer of the current node.
      */
      if (current_node->previous != NULL || current_node->next != NULL) {
        
        if (current_node->next == NULL) {           
           list->head = current_node->previous;
           list->head->next = NULL;

        } else if (current_node->previous == NULL) {
          list->tail = current_node->next;
          list->tail->previous = NULL;

        } else {
          current_node->previous->next = current_node->next;
          current_node->next->previous = current_node->previous;
        }

      } else {
        list->tail = NULL;
        list->head = NULL;
      }
      
      // Free the current node and decrement the size of the list
      free(current_node);
      list->list_size--;
      return SUCCESS_REMOVE;
    }

    current_node = current_node->next;
  }
  return FAIL_REMOVE;
}

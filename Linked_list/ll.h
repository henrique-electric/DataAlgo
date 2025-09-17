#ifndef LL_H
#define LL_H

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS_PUSH 0
#define FAILED_PUSH 1

#define SUCCESS_DESTROY 0
#define FAILED_DESTROY 1

#define SUCCESS_POP 0
#define FAIL_POP 1

#define SUCCESS_REMOVE 0
#define FAIL_REMOVE 1

typedef struct node {
  int data;
  struct node *next;
  struct node *previous;
} node_t;

typedef struct list {
  size_t list_size;
  node_t *head;
  node_t *tail;
} list_t;

list_t *create_list(void);

int list_push(list_t *list, int data);
int list_pop(list_t *list);
int list_destroy(list_t *list);
int list_remove(list_t *list, int data);

node_t *new_node(int data);
#endif // !LL_H

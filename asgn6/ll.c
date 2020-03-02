#include "ll.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int looks;
extern double links;

// Creates a new linked list node for goodspeak words and set next pointer NULL
ListNode *ll_node_create(GoodSpeak *gs) {
  ListNode *n = (ListNode *)malloc(sizeof(ListNode));
  n->gs = gs;
  n->next = NIL;

  return n;
}

// delete single node
void ll_node_delete(ListNode *n) {
  gs_delete(n->gs);
  // free(n);
  n = NULL;
}

// deletes whole list
void ll_delete(ListNode *head) {
  if (head) {
    ListNode *temp;
    while (head != NIL) {
      temp = head;
      head = head->next;
      ll_node_delete(temp);
      // free(temp);
    }
  }
  head = NULL;
}

GoodSpeak *ll_node_gs(ListNode *n) { return n->gs; }

// Inserts a new node to connect with head
ListNode *ll_insert(ListNode **head, GoodSpeak *gs) {
  // if word doesn't exist in any node, make new one else replace the data
  // inside
  if (ll_lookup(&*head, gs->oldspeak) == NIL) {
    ListNode *l = ll_node_create(gs);
    l->next = *head;
    *head = l;
    return *head;
  } else {
    ll_lookup(&*head, gs->oldspeak)->gs = gs;
    return *head;
  }
}

// Searches for the word in the Nodes and returns head pointer if found
ListNode *ll_lookup(ListNode **head, char *key) {
  looks += 2;
  // Default=don't move node to front
  if (move_to_front != true) {
    if (*head && key) {
      ListNode *current = *head;
      while (current != NIL) {
        links += 1;
        if (strcmp(current->gs->oldspeak, key) == 0) {
          return current;
        }
        current = current->next;
      }
    }
    return NIL;
  } else if (move_to_front == true) { // if move_to_front, then search Nodes
    if (*head && key) {               // will move to the front
      ListNode *current = *head;
      ListNode *previous = NIL;
      while (current != NIL) {
        links += 1;
        if (strcmp(current->gs->oldspeak, key) == 0) {
          if (previous != NIL) {
            previous->next = current->next;
            current->next = *head;
            *head = current;
          }
          return *head;
        }
        previous = current;
        current = current->next;
      }
    }
  }
  return NIL;
}

// print node current
void ll_node_print(ListNode *n) {
  while (n != NIL) {
    printf("%s", n->gs->oldspeak);
    n = n->next;
  }
}

// print entire list
void ll_print(ListNode *head) {

  if (head) {
    ListNode *current = head;
    while (current != NIL) {
      printf("%s ", current->gs->oldspeak);
      if (current->gs->newspeak != NULL) {
        printf("-> %s\n", current->gs->newspeak);
      } else {
        printf("\n");
      }
      current = current->next;
    }
  }
}

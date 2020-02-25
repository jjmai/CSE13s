#include "ll.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ListNode * ll_node_create ( GoodSpeak *gs) {
    ListNode * n=(ListNode *)malloc(sizeof(ListNode));
    n->next=NIL;

    return n;
}

void ll_node_delete ( ListNode *n) {
    if(n) {
        if(n->gs) {
            free(n->gs);
        }
        free(n);
    }
}

void ll_delete ( ListNode * head ) {
    if(head) {
        ListNode *current = head;
        ListNode *next;
        while (current != NIL) {
            next = current->next;
            free(current);
            current = next;
        }
        head = NIL;
    }
}

GoodSpeak *ll_node_gs(ListNode *n) {

}

ListNode * ll_insert ( ListNode ** head , GoodSpeak *gs) {
    ListNode *l=ll_node_create(gs);
    l->gs=gs;
    l->next=*head;
    *head=l;
    return *head;

}
ListNode * ll_lookup ( ListNode ** head , char * key ) {
    if(move_to_front !=true) {
        if (*head && key) {
            ListNode *current = *head;
            while (current != NIL) {
                if (strcmp(current->gs->oldspeak, key) == 0) {
                    return current;
                }
                current = current->next;
            }
        }
    } else if (move_to_front==true) {
        if (*head && key) {
            ListNode *current = *head;
            ListNode *previous = NULL;
            while (current != NIL) {
                if (strcmp(current->gs->oldspeak, key) == 0) {
                    previous->next=current->next;
                    current->next=*head;
                    *head=current;
                    return *head;
                }
                previous=current;
                current = current->next;
            }
        }
    }
    return NIL;
}

void ll_node_print(ListNode *n) {
    while(n!=NIL) {
        printf("%s",n->gs->oldspeak);
        n=n->next;
    }

}

void ll_print(ListNode *head) {

    if(head) {
        ListNode *current=head;
        while(current !=NIL) {
            printf("%s %s",current->gs->oldspeak,current->gs->newspeak);
            current=current->next;
        }
    }

}






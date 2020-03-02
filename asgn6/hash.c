#include "hash.h"
#include "ll.h"
#include "speck.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern float hload;

HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3; // Il nome della rosa
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }

  return (HashTable *)NIL;
}
// deletes Hash Table at every index
void ht_delete(HashTable *ht) {

  // ListNode *temp;
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NIL) {
      free(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
}

// Searches the HashTable at the hashed index for the word that is needed
ListNode *ht_lookup(HashTable *ht, char *key) {

  uint32_t h = hash(ht->salt, key) % ht->length;
  // Calls ll_lookup to see if word exists in that pointer of head
  for (ListNode *temp2 = ht->heads[h]; temp2 != NIL; temp2 = temp2->next) {
    if (strcmp(ll_lookup(&temp2, key)->gs->oldspeak, key) == 0) {
      return ll_lookup(&temp2, key);
    }
  }
  return NIL;
}
// Insert Linked Node at index
void ht_insert(HashTable *ht, GoodSpeak *gs) {
  uint32_t h = hash(ht->salt, gs->oldspeak) % ht->length;
  if (ht->heads[h] == NIL) {
    ht->heads[h] = ll_node_create(gs); // if empty then just insert
  } else {
    ht->heads[h] = ll_insert(&ht->heads[h], gs); // if not empty,set pointer
  }
}

// prints Hash table values
void ht_print(HashTable *h) {
  if (h) {
    for (uint32_t i = 0; i < h->length; i++) {
      for (ListNode *temp = h->heads[i]; temp != NULL; temp = temp->next) {
        printf("%d %s %s ->", i, temp->gs->oldspeak, temp->gs->newspeak);
      }
    }
  }
}

uint32_t ht_count(HashTable *h) {
  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i] != NULL) {
      hload += 1;
    }
  }
  // printf("%f %d",hload,h->length);
  double hl = 100 * (hload / h->length);
  return hl;
}

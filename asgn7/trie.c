#include "trie.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>

TrieNode *trie_node_create(uint16_t code) {
  TrieNode *t = (TrieNode *)malloc(sizeof(TrieNode));
  for (int i = 0; i < ALPHABET; i++) {
    t->children[i] = NULL;
  }
  t->code = code;
  return t;
}

void trie_node_delete(TrieNode *n) {
  // n->code=0;
  free(n);
  n = NULL;
}

void trie_reset(TrieNode *root) {
  for (int i = 0; i < ALPHABET; i++) {
    if (root->children[i]) {
      trie_delete(root->children[i]);
    }
  }
}

TrieNode *trie_create(void) {
  TrieNode *root = trie_node_create(EMPTY_CODE);
  return root;
}

void trie_delete(TrieNode *n) {
  // TrieNode *temp = n;
  for (int i = 0; i < ALPHABET; i++) {
    if (n->children[i]) {
      trie_delete(n->children[i]);
      // trie_node_delete(temp->children[i]);
      // temp->children[i]->code = 0;
      // free(temp->children[i]);
      n->children[i] = NULL;
    }
  }
  // trie_node_delete(temp);
  trie_node_delete(n);
  n = NULL;
}

//checks if there are childrens
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  if (n->children[sym]) {
    return n->children[sym];
  }
  return NULL;
}

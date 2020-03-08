#include "code.h"
#include "io.h"
#include "trie.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  //FILE *fpin = stdin;
  int infile;
  int outfile;
  if (argc < 2 ) {
    infile=0;
    outfile=0;
    //infile = open("test.txt", O_RDONLY | O_CREAT);
    //outfile = open("test2.txt", O_WRONLY | O_CREAT);
}

  int opt;
  int letter = 0;
  while ((opt = getopt(argc, argv, "vio")) != EOF) {
    switch (opt) {
    case 'v':
      letter = 'v';
      break;
    case 'i':
      infile = open(optarg, O_RDONLY | O_CREAT);

      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT);

      break;
    default:
      exit(1);
    }
  }

  TrieNode *root = trie_create();
  TrieNode *curr_node = root;
  TrieNode *prev_node = NULL;
  uint8_t curr_sym = 0;
  uint8_t prev_sym = 0;
  uint16_t next_code = START_CODE;

  
  while (read_sym(infile, &curr_sym) == true) {

    TrieNode *next_node = trie_step(curr_node, curr_sym);
    if (next_node != NULL) {
      prev_node = curr_node;
      curr_node = next_node;
    } else {
      buffer_pair(outfile,curr_node->code,curr_sym,log2(next_code)+1);
      curr_node->children[curr_sym] = trie_node_create(next_code);
      //printf("%d %c\n", curr_node->children[curr_sym]->code, curr_sym);
      curr_node = root;
      next_code += 1;
    }
    if (next_code == MAX_CODE) {
      trie_reset(root);
      curr_node = root;
      next_code = START_CODE;
    }
    // printf("%d",curr_node->children[curr_sym]->code);
    prev_sym = curr_sym;
  }
  return 0;
}

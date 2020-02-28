#include "bf.h"
#include "gs.h"
#include "hash.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#define REGEX "[a-zA-Z-]+"
#define THIRTY_BIT (1 << 30) - 1
#define HASH_DEFAULT 10000
bool move_to_front;

int main(int argc, char *argv[]) {
  int opt;
  int letter = 0;
  char *word;
  char *word2;
  char words[256];
  int j_index = 0;
  // char ch[256];
  int hash_size = HASH_DEFAULT;
  int bloom_size = THIRTY_BIT;
  bool check = true;
  FILE *badfile;
  FILE *goodfile;
  char *filename = "test.txt";
  char *filename2 = "test2.txt";
  badfile = fopen(filename, "r");
  goodfile = fopen(filename2, "r");
  regex_t regex;
  regcomp(&regex, REGEX, REG_EXTENDED);

  while ((opt = getopt(argc, argv, "sh:f:mb")) != EOF) {
    switch (opt) {
    case 's':
      letter = 's';
      break;
    case 'h':
      hash_size = atoi(optarg);
      break;
    case 'f':
      bloom_size = atoi(optarg);
      break;
    case 'm':
      if (check != false) {
        check = false;
        move_to_front = true;
      }
      break;
    case 'b':
      if (check != false) {
        check = false;
        move_to_front = false;
      }
      break;
    default:
      exit(1);
    }
  }
  BloomFilter *bf = bf_create(bloom_size);
  HashTable *ht = ht_create(hash_size);
  char *joycamp[hash_size];

  while ((word = next_word(badfile, &regex)) != NULL) {
    bf_insert(bf, word);
    GoodSpeak *gs = gs_create(word, NULL);
    ht_insert(ht, gs);
  }
  while ((word = next_word(goodfile, &regex)) &&
         (word2 = next_word(goodfile, &regex)) != NULL) {
    bf_insert(bf, word);
    GoodSpeak *gs = gs_create(word, word2);
    ht_insert(ht, gs);
  }
  while (scanf("%s", words) != EOF) {
    if (bf_probe(bf, words) == true) {
      if (ht_lookup(ht, words) != NIL &&
          ht_lookup(ht, words)->gs->newspeak == NIL) {
        joycamp[j_index] = words;
        j_index += 1;
      }
    }
  }

  return 0;
}

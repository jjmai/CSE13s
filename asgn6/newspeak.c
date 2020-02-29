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
#define REGEX "[a-zA-Z'-]+"
#define THIRTY_BIT (1 << 30) - 1
#define HASH_DEFAULT 10000

bool move_to_front;
float bload;
float hload;

int main(int argc, char *argv[]) {
  FILE *fp=stdin;
  int opt;
  int letter = 0;
  bload=0;
  hload=0;
  char joycamp_letter[512] =
      "Dear Comrade,\n\nYou have chosen to use degenerate words that may cause "
      "hurt feelings or cause comrades to think unpleasant thought. This is "
      "doubleplus bad. To correct your wrongthink and preserve community "
      "consensus we will be sending you to joycamp administered by Miniluv.\n\n"
      "Your errors:\n\n";
  char translation_letter[512] =
      "Dear Comarde,\n\nSubmitting your text helps to preserve feelings and "
      "prevent badthink. Some of the words that you used are not goodspeak. "
      "The list shows how to turn the oldspeak words into newspeak.\n\n";
  char *word;
  char *word2;
  //char *word3;
  char *words;
  int j_index = 0;
  int t_index = 0;
  int hash_size = HASH_DEFAULT;
  int bloom_size = THIRTY_BIT;
  bool check = true;
  FILE *badfile;
  FILE *goodfile;
  char *filename = "oldspeak.txt";
  char *filename2 = "newspeak.txt";
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
  char *translation_old[hash_size];
  char *translation_new[hash_size];

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
  while ((words= next_word(fp, &regex)) != NULL) {
    if (bf_probe(bf, words) == true) {
      if (ht_lookup(ht, words) != NIL &&
          ht_lookup(ht, words)->gs->newspeak == NIL) {
        joycamp[j_index] = ht_lookup(ht, words)->gs->oldspeak;
        j_index += 1;
      } else if (ht_lookup(ht, words) != NIL &&
                 ht_lookup(ht, words)->gs->newspeak != NIL) {
        translation_old[t_index] = ht_lookup(ht, words)->gs->oldspeak;
        translation_new[t_index] = ht_lookup(ht, words)->gs->newspeak;
        t_index += 1;
      }
    }
  }
  if (letter != 's') {
    if (j_index > 0 && t_index <= 0) {
      printf("%s", joycamp_letter);
      for (int i = 0; i < j_index; i++) {
        printf("%s\n", joycamp[i]);
      }
    } else if (t_index > 0 && j_index <= 0) {
      printf("%s", translation_letter);
      for (int i = 0; i < t_index; i++) {
        printf("%s -> ", translation_old[i]);
        printf("%s\n", translation_new[i]);
      }
    } else if (t_index > 0 && j_index > 0) {
      printf("%s", joycamp_letter);
      for (int i = 0; i < j_index; i++) {
        printf("%s\n", joycamp[i]);
      }
      printf("\n\nThink of these words on your vacation!\n\n");
      for (int i = 0; i < t_index; i++) {
        printf("%s -> ", translation_old[i]);
        printf("%s\n", translation_new[i]);
      }
    }
  }
  if (letter =='s') {
    float h=ht_count(ht);
    h=100.00* (h/hash_size);
    printf("%f %s\n",h,"%");
    float b=100.00* (bload/bloom_size);
    printf("%f %s\n",b,"%");
}

  return 0;
}

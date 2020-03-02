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
#define REGEX "[a-zA-Z0-9'-_]+" // Regular Expresison
#define TWENTY_BIT (1 << 20)    // Default size for BF
#define HASH_DEFAULT 10000      // Default size for HT

bool move_to_front;
double bload;
double hload;
int looks;
double links;

int main(int argc, char *argv[]) {
  FILE *fp = stdin;
  int opt;
  int letter = 0;
  int maxword = 0; // to count number of words possible for array
  bload = 0;
  hload = 0;
  looks = 0;
  links = 0;
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
  char *words;
  int j_index = 0; // index for fobidden word array
  int t_index = 0; // index for translation words array
  int hash_size = HASH_DEFAULT;
  int bloom_size = TWENTY_BIT;
  bool check = true;
  FILE *badfile;
  FILE *goodfile;
  char *filename = "badspeak.txt";
  char *filename2 = "goodspeak.txt";
  badfile = fopen(filename, "r");
  goodfile = fopen(filename2, "r");
  regex_t regex;
  regcomp(&regex, REGEX, REG_EXTENDED);

  while ((opt = getopt(argc, argv, "sh:f:mb")) != EOF) {
    switch (opt) {
    case 's':
      letter = 's'; // notify that print statistic only
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
  // reads in forbidden word file .txt and stores in BF and HT
  while ((word = next_word(badfile, &regex)) != NULL) {
    bf_insert(bf, word);
    GoodSpeak *gs = gs_create(word, NULL);
    ht_insert(ht, gs);
    maxword += 1;
  }
  // Reads in translation words in .txt and stores in BF and HT
  while ((word = next_word(goodfile, &regex)) &&
         (word2 = next_word(goodfile, &regex)) != NULL) {
    bf_insert(bf, word);
    GoodSpeak *gs = gs_create(word, word2);
    ht_insert(ht, gs);
    maxword += 1;
  }
  char *joycamp[maxword + 1];         // store forbidden words used
  char *translation_old[maxword + 1]; // store old translation word
  char *translation_new[maxword + 1]; // stroe new translation word
  for (int i = 0; i < maxword + 1; i++) {
    joycamp[i] = NULL;
    translation_old[i] = NULL;
    translation_new[i] = NULL;
  }

  // READS in stdin/file of words and store in appropraite array if exitst in HT
  while ((words = next_word(fp, &regex)) != NULL) {
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
  // if -s flag not implemented, then print the Letter and words
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
  // prints Stats if -s flag
  if (letter == 's') {
    printf("Seeks: %d\n", looks);
    printf("Average Seek Length: %f\n", links / looks);
    double hl = ht_count(ht);
    printf("HashTable Load %f %s\n", hl, "%");
    double bb = bf_count(bf);
    printf("Bloom Filter Load: %f %s\n", bb, "%");
  }
  bf_delete(bf);
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NULL) {
      ll_delete(ht->heads[i]);
    }
  }
  ht_delete(ht);
  fclose(badfile);
  fclose(goodfile);
  regfree(&regex);
  return 0;
}

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
#include <string.h>
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
  int hash_size = HASH_DEFAULT;
  int bloom_size = TWENTY_BIT;
  bool check = true; // checker for movetofront
  bool f = false;    // checks if there is forbidden word
  bool t = false;    // checks if there is translation word
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
  }
  // Reads in translation words in .txt and stores in BF and HT
  while ((word = next_word(goodfile, &regex)) &&
         (word2 = next_word(goodfile, &regex)) != NULL) {
    bf_insert(bf, word);
    GoodSpeak *gs = gs_create(word, word2);
    ht_insert(ht, gs);
  }
  ListNode *forbidden = NULL;   // linked list for forbidden word
  ListNode *translation = NULL; // linked list for translation word

  // READS in stdin/file of words and store in appropraite array if exitst in HT
  while ((words = next_word(fp, &regex)) != NULL) {
    if (bf_probe(bf, words) == true) {
      if (ht_lookup(ht, words) != NIL &&
          ht_lookup(ht, words)->gs->newspeak == NIL) {
        ll_insert(&forbidden, ht_lookup(ht, words)->gs);
        f = true;
      } else if (ht_lookup(ht, words) != NIL &&
                 ht_lookup(ht, words)->gs->newspeak != NIL) {
        ll_insert(&translation, ht_lookup(ht, words)->gs);
        t = true;
      }
    }
  }
  // if -s flag not implemented, then print the Letter and words
  if (letter != 's') {
    // only if forbidden word
    if (f == true && t == false) {
      printf("%s", joycamp_letter);
      ll_print(forbidden);
    } else if (t == true && f == false) { // only if translation
      printf("%s", translation_letter);
      ll_print(translation);
    } else if (f == true && t == true) { // if both forbidden and translation
      printf("%s", joycamp_letter);
      ll_print(forbidden);
      printf("\n\nThink of these words on your vacation!\n\n");
      ll_print(translation);
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
  ht_delete(ht);
  ll_delete(forbidden);
  ll_delete(translation);
  fclose(badfile);
  fclose(goodfile);
  regfree(&regex);
  return 0;
}

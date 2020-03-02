#include "bf.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern double bload;

BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7; // U.S. Constitution
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3; // Il nome della rosa
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0; // The Cremation of Sam McGee
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    return bf;
  }
  return (BloomFilter *)NIL;
}

void bf_delete(BloomFilter *bf) {
  free(bf->filter);
  // free(bf);
}

//Inserts hashed words in the bitvector 
void bf_insert(BloomFilter *bf, char *key) {
  uint32_t answer = 0;
  answer = hash(bf->primary, key) % bf_length(bf);
  bv_set_bit(bf->filter, answer);
 
  answer = hash(bf->secondary, key) % bf_length(bf);
  bv_set_bit(bf->filter, answer);
  
  answer = hash(bf->tertiary, key) % bf_length(bf);
  bv_set_bit(bf->filter, answer);
  
}

//checks if the word is in Bloom Filter
bool bf_probe(BloomFilter *bf, char *key) {
  uint32_t check1 = 0, check2 = 0, check3 = 0;
  check1 = hash(bf->primary, key) % bf->filter->length;
  check2 = hash(bf->secondary, key) % bf->filter->length;
  check3 = hash(bf->tertiary, key) % bf->filter->length;
  if (bv_get_bit(bf->filter, check1) == 1 &&
      bv_get_bit(bf->filter, check2) == 1 &&
      bv_get_bit(bf->filter, check3) == 1) {
    return true;
  }
  return false;
}
// size of Bloom Filter
uint32_t bf_length(BloomFilter *b) { return b->filter->length; }

// Returns the Bloom Filter Load
uint32_t bf_count(BloomFilter *b) {
  for (uint32_t i = 0; i < bf_length(b); i++) {
    if (bv_get_bit(b->filter, i) == 1) {
      bload += 1;
    }
  }
  double bb = 100 * (bload / bf_length(b));

  return bb;
}

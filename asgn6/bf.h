#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __BF_H__
#define __BF_H__

#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>

// typedef struct BloomFilter BloomFilter;

typedef struct BloomFilter {
  uint64_t primary[2]; // Provide for three different hash functions
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
} BloomFilter;

BloomFilter *bf_create(uint32_t size);

void bf_delete(BloomFilter *b);

uint32_t bf_length(BloomFilter *b);

void bf_insert(BloomFilter *b, char *key);

bool bf_probe(BloomFilter *b, char *key);

uint32_t bf_count(BloomFilter *b);

#endif

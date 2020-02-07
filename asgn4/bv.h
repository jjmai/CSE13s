#ifndef __BV_H__
#define __BV_H__

#include <inttypes.h>
#include <stdbool.h>

typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

BitVector *bv_create(uint32_t bit_len);

void bv_delete(BitVector *v);

uint32_t bv_get_len(BitVector *v);

void bv_set_bit(BitVector *v, uint32_t i);

void bv_clr_bit(BitVector *v, uint32_t i);

uint8_t bv_get_bit(BitVector *v, uint32_t i);

void bv_set_all_bits(BitVector *v);

#endif

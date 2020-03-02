#include "bv.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

BitVector *bv_create(uint32_t bit_len) {

  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  v->length = bit_len;
  v->vector = (uint8_t *)calloc(v->length, sizeof(uint8_t));
  return v;
}

void bv_delete(BitVector *v) {
  free(v->vector);
  free(v);
}

uint32_t bv_get_len(BitVector *v) { return v->length; }

void bv_set_bit(BitVector *v, uint32_t i) { v->vector[i / 8] |= 1 << (i % 8); }

void bv_clr_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] &= ~(1 << (i % 8));
}

uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  return v->vector[i / 8] >> (i % 8) & 1;
}

// void bv_set_all_bits(BitVector *v) {
// for (uint32_t i = 0; i < bv_get_len; i++) {
// v->vector[i / 8] |= 1 << (i % 8);
//}
//}

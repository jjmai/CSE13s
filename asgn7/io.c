#include "io.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BLOCK 4096
// static uint8_t *words[BLOCK] = {NULL};
static uint8_t buffer[BLOCK] = {0};
static int x = 0;

// make enum make if statement if block is empty or full then read in
// else store in arrya and check idnex for each symbol
bool read_sym(int infile, uint8_t *sym) {

  if (x == 0 || x > BLOCK) {

    if (read(infile, buffer, BLOCK) == 0) {
      return false;
    }
  }
  // memcpy(words,buffer,sizeof(buffer));
  if (buffer[x] != '\0') {
    *sym = buffer[x];
    x = (x + 1) % BLOCK;
    return true;
  }
  return false;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  // char[BLOCK];
  uint16_t c = code;
  uint16_t c_length = log2(c) + 1;
  uint16_t temp = 0, reverse = 0;
  for (uint16_t i = 0; i < c_length; i++) {
    temp = (c & (1 << i));
    if (temp) {
      reverse |= (1 << ((c_length - 1) - i));
    }
  }
  for (uint16_t i = 0; i < bitlen - c_length; i++) {
    reverse = reverse << 1;
  }

  uint8_t s = sym;
  uint8_t s_length = log2(s)+1;
  uint8_t temp2 = 0, reverse2 = 0;
  for (uint8_t i = 0; i < s_length; i++) {
    temp2 = (s & (1 << i));
    if (temp2) {
      reverse2 |= (1 << ((s_length - 1) - i));
    }
  }
  for (uint8_t i = 0; i < bitlen - s_length; i++) {
    reverse2 = reverse2 << 1;
  }
  uint32_t combine=0;
  combine = reverse << s_length | reverse2; 
  write(outfile,&combine,sizeof(combine));
}

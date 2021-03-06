#include "io.h"
#include "code.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void clear_words();
#define BLOCK 4096
double csize;  //extern var for compress stat
double dsize;  //extern var for uncompres stat

static uint8_t word[BLOCK] = {0};    // array for storing encoded bits to be
                                     // written
static uint8_t buffer[BLOCK] = {0};  // array for reading in 4KB for encode
static uint8_t buffer2[BLOCK] = {0}; // array for reading in 4kb  for decode
static uint8_t bufferd[BLOCK] = {0}; // array for storeing symbol for decode
static int x = 0;                    // index for encode buffer
static int bit_index = 0;            // index for bit placing
static int d = 0;                    // index for decode buffer
static int end = 0;                  // number to indicate end of file

void read_header(int infile, FileHeader *header) {
  // header->magic = MAGIC;
  struct stat protection;
  fstat(infile, &protection);
  header->protection = protection.st_mode;
  //fails if header not equal
  read(infile, header, sizeof(FileHeader));
  if (header->magic != 0x8badbeef) {
    printf("bad magic number");
    exit(1);
  }
  dsize += sizeof(FileHeader);
}

void write_header(int outfile, FileHeader *header) {
  header->magic = MAGIC;
  struct stat protection;
  fstat(outfile, &protection);
  header->protection = protection.st_mode;
  write(outfile, header, sizeof(FileHeader));
  csize += sizeof(FileHeader);
}

bool read_sym(int infile, uint8_t *sym) {
  // reads from infile
  if (x == 0 || x > BLOCK || x == end) {
    int n = read(infile, buffer, BLOCK);
    end = n;
    dsize += n;
    if (n == 0) {
      return false;
    }
  }
  // false if no bytes read
  *sym = buffer[x];
  x = (x + 1) % BLOCK;
  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  bitlen = (int)bitlen;
  uint16_t c = code;
  uint16_t temp = 0; 
  // sets a 1 or 0 to word[] array
  for (uint16_t i = 0; i < bitlen; i++) {
    if (bit_index == BLOCK * 8) {
      flush_pairs(outfile);
      bit_index=0;
    }
    temp = (c & (1 << i));
    if (temp) {
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      bit_index++;
    }
  }

  uint8_t s = sym;
  uint8_t temp2 = 0; 
  uint8_t s_length = (int)log2(s) + 1; // check bits of current sym
  // set 1 or 0 to word array
  for (uint8_t i = 0; i < s_length; i++) {
    if (bit_index == BLOCK * 8) {
      flush_pairs(outfile);
      bit_index=0;
    }
    temp2 = (s & (1 << i));
    if (temp2) {
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      bit_index++;
    }
  }
  // bit shifts and place trailing 0
  for (uint8_t i = 0; i < 8 - s_length; i++) {

    if (bit_index == BLOCK * 8) {
      flush_pairs(outfile);
      bit_index=0;
    }
    word[bit_index / 8] &= ~(1 << (bit_index % 8));
    bit_index++;
  }
}

// writes out pairs
void flush_pairs(int outfile) {

  write(outfile, word, bit_index);
  csize += bit_index / 8;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {

  bitlen = (int)bitlen;
  // reads in BLOCK of bits
  if (bit_index == 0 || bit_index == BLOCK * 8) {
    bit_index = 0;
    int n = read(infile, buffer2, BLOCK);
    end = n;
    csize += n;
    if (n == 0) {
      return false;
    }
  }

  uint16_t temp = 0;
  uint16_t array[1] = {0}; // array to store bits of char
  // puts 1 or 0 to array
  for (uint8_t i = 0; i < bitlen; i++) {

    if (bit_index == BLOCK * 8) {
      bit_index = 0;
      int n = read(infile, buffer2, BLOCK);
      end = n;
      csize += n;
      if (n == 0) {
        return false;
      }
    }
    temp = (buffer2[bit_index / 8] >> (bit_index % 8) & 1);
    if (temp == 1) {
      array[0] |= 1 << (i % 16);
    } else {
      array[0] &= ~(1 << (i % 16));
    }
    bit_index++;
  }
  *code = array[0];

  uint8_t temp2 = 0;
  uint8_t array2[1] = {0}; // array for sym
  // puts 1 or 0
  for (int i = 0; i < 8; i++) {

    if (bit_index == BLOCK * 8) {
      bit_index = 0;
      int n = read(infile, buffer2, BLOCK);
      end = n;
      csize += 1;
      if (n == 0) {
        return false;
      }
    }
    temp2 = (buffer2[bit_index / 8] >> (bit_index % 8) & 1);
    if (temp2 == 1) {
      array2[i / 8] |= 1 << (i % 8);
    } else {
      array2[i / 8] &= ~(1 << (i % 8));
    }

    bit_index++;
  }
  *sym = array2[0];
  // if reaches end then break
  if (*code == STOP_CODE && *sym == 0) {
    // printf("NICE");
    return false;
  }

  return true;
}

// store each char at each index
void buffer_word(int outfile, Word *w) {

  if (d == BLOCK) {
    flush_words(outfile);
  }
  for (uint64_t i = 0; i < w->len; i++) {
    bufferd[d] = w->syms[i];
    d++;
  }
}

// write buffer out
void flush_words(int outfile) {
  write(outfile, bufferd, d);
  dsize += d;
  d = 0;
}

// reset word array?
void clear_words(void) {
  for (uint16_t i = 0; i < BLOCK; i++) {
    if (word[i]) {
      // free(words[i]);
      word[i / 8] &= ~(1 << (i % 8));
    }
  }
}

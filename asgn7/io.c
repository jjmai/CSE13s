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
void buffer_check();
bool buffer2_check();
#define BLOCK 4096
// static uint16_t *words[BLOCK] = {NULL};
static uint8_t word[BLOCK] = {0};
static uint8_t buffer[BLOCK] = {0};
static uint8_t buffer2[BLOCK] = {0};
static uint8_t bufferd[BLOCK] = {0};
static int x = 0; // index for 4KB
static int bit_index = 0;
static int d = 0;
static int end = 0;

void read_header(int infile, FileHeader *header) {
  // header->magic = MAGIC;
  struct stat protection;
  fstat(infile, &protection);
  header->protection = protection.st_mode;
  read(infile,header,sizeof(FileHeader));
  // if(read(infile,header,sizeof(FileHeader)) != sizeof(FileHeader)) {
  // printf("bad magic number");
  //  exit(1);
  // }
  // printf("%lu ",sizeof(header->magic));
  // printf("%lu ",sizeof(header->protection));
  // printf("%d ",header->magic);
  // printf(" %d ",header->protection);
  // if(header->magic != MAGIC) {
  // printf("bad magic number\n");
  // exit(1);
  // }
}

void write_header(int outfile, FileHeader *header) {
  header->magic = MAGIC;
  struct stat protection;
  fstat(outfile, &protection);
  header->protection = protection.st_mode;
  write(outfile, header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
  // int end=0;
  if (x == 0 || x > BLOCK) {
    int n = read(infile, buffer, BLOCK);
    end = n;
    if (n == 0) {
      return false;
    }
  }
  if (x == end || buffer[x] == '\0') {
    return false;
  }
  *sym = buffer[x];
  x = (x + 1) % BLOCK;
  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  bitlen = (int)bitlen;
  // printf("%d %d %d. ",code,sym,bitlen);
  uint16_t c = code;                    // temp varaible for code (1,2,3...)
  uint16_t c_length = (int)log2(c) + 1; // length in bits of code
  uint16_t temp = 0, reverse = 0;       // reverse = reversed bits
  for (uint16_t i = 0; i < bitlen; i++) {
    temp = (c & (1 << i));
    if (temp) {
      reverse |= (1 << ((c_length - 1) - i));
      buffer_check(outfile);
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      buffer_check(outfile);
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      bit_index++;
    }
  }

  uint8_t s = sym;                     // tmep var for symbol ('a','b',c')
  uint8_t s_length = (int)log2(s) + 1; // bit length of symbol
  uint8_t temp2 = 0, reverse2 = 0;
  for (uint8_t i = 0; i < s_length; i++) {
    temp2 = (s & (1 << i));
    if (temp2) {
      reverse2 |= (1 << ((s_length - 1) - i));
      buffer_check(outfile);
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      buffer_check(outfile);
      word[bit_index / 8] &= ~(1 << (bit_index % 8));

      bit_index++;
    }
  }

  for (uint8_t i = 0; i < 8 - s_length; i++) {
    reverse2 = reverse2 << 1;
    buffer_check(outfile);
    word[bit_index / 8] &= ~(1 << (bit_index % 8));
    bit_index++;
  }

  if (bit_index == BLOCK * 8) {
    flush_pairs(outfile);
    clear_words();
  }
}

void flush_pairs(int outfile) {

  write(outfile, word, bit_index);
  for (int i = 0; i < bit_index; i++) {
    // word[i / 8] &= ~(1 << (i % 8));
    word[i] = '\0';
  }
  bit_index = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  // printf("hi");
  bitlen = (int)bitlen;
  if (bit_index == 0 || bit_index == BLOCK * 8) {
    bit_index = 0;
    int n = read(infile, buffer2, BLOCK);
    end = n;
    if (n == 0) {
      return false;
    }
  }

  uint16_t temp = 0;
  //uint8_t c =0;
  uint8_t array[1] ={0};
  for (int i = 0; i < bitlen; i++) {
    if (buffer2_check(infile) == false) {
      return false;
    }
    temp = (buffer2[bit_index / 8] >> (bit_index % 8) & 1);
    if(temp ==1) {
      array[0] |= 1 << (i%8);    
  } else {
     array[0] &= ~(1 << (i%8));

  }
    //if((buffer2[bit_index / 8] & (1 <<(bit_index % 8))) !=0) {
     // array[0] = array[0] |= 1 << (i%8);
 // } else {
   //   array[0] &= ~(1 << (i%8));
 // }
    
    bit_index++;
    //c+=temp * exp(i);
    //c = temp | (c << 1);
  }
  *code = array[0];
   //printf("%d \n ",*code);

  uint8_t temp2 = 0;
  //uint8_t s=0;
  uint8_t array2[1]= {0};
  for (int i = 0; i < 8; i++) {
    if (buffer2_check(infile) == false) {
      return false;
    }
    temp2 = (buffer2[bit_index / 8] >> (bit_index % 8) & 1);
    if(temp2 == 1) {
      array2[0] |= 1 <<(i%8);
  } else {
      array2[0] &= ~(1 << (i%8));
  }
    //if((buffer2[bit_index/8] & (1 <<(bit_index %8)))!=0) {
      //array2[0] |= 1 << (i%8);
  //}else {
    // array2[0] &= ~(1 << (i % 8));
 // }

    bit_index++;
    //s+= temp2* exp(i);
   // s = temp2 | (s << 1);
  }
  *sym = array2[0];
  //printf("%d \n",*sym);
  if (*code == STOP_CODE && *sym == 0) {
    return false;
  }
  //printf("%c ?\n", *sym);
  return true;
}

void buffer_word(int outfile, Word *w) {

  //printf("%s ",w->syms);
  if (d == BLOCK) {
    flush_words(outfile);
    d = 0;
  }
  for(uint64_t i=0;i<w->len;i++) {
    bufferd[d]=w->syms[i];
    //printf("%c ",bufferd[d]);
    d++;
  }
  
}
void flush_words(int outfile) {  
  //for(int i=0;i<d;i++) {
   //printf("%c ",bufferd[i]); 
 // }
  write(outfile, bufferd, d);
 
}

void buffer_check(int outfile) {
  if (bit_index >= BLOCK * 8) {
    flush_pairs(outfile);
  }
}

bool buffer2_check(int infile) {
  if (bit_index >= BLOCK * 8 || bit_index / 8 >= end) {
    int n = read(infile, buffer2, BLOCK);
    end = n;
    bit_index = 0;
  }
  if (end == 0) {
    return false;
  }
  return true;
}
void clear_words(void) {
  for (uint16_t i = 0; i < BLOCK; i++) {
    if (word[i]) {
      // free(words[i]);
      word[i / 8] &= ~(1 << (i % 8));
    }
  }
}

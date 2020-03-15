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

static uint8_t word[BLOCK] = {0}; //array for storing encoded bits to be written
static uint8_t buffer[BLOCK] = {0}; //array for reading in 4KB for encode
static uint8_t buffer2[BLOCK] = {0};  //array for reading in 4kb  for decode
static uint8_t bufferd[BLOCK] = {0};  //array for storeing symbol for decode
static int x = 0; // index for encode buffer
static int bit_index = 0;  //index for bit placing
static int d = 0;    //index for decode buffer
static int end = 0;   //number to indicate end of file


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
}

void write_header(int outfile, FileHeader *header) {
  header->magic = MAGIC;
  struct stat protection;
  fstat(outfile, &protection);
  header->protection = protection.st_mode;
  write(outfile, header, sizeof(FileHeader));
}

bool read_sym(int infile, uint8_t *sym) {
  //reads from infile
  if (x == 0 || x > BLOCK) {
    int n = read(infile, buffer, BLOCK);
    end = n;
    if (n == 0) {
      return false;
    }
  }
  //false if no bytes read
  if (x == end ) {
    return false;
  }
  *sym = buffer[x];
  x = (x + 1) % BLOCK;
  return true;
}

void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {

  bitlen = (int)bitlen;
  uint16_t c = code;      
  uint16_t temp = 0; 
  //sets a 1 or 0 to word[] array   
  for (uint16_t i = 0; i < bitlen; i++) {
    temp = (c & (1 << i));
    if (temp) {
      buffer_check(outfile);
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      buffer_check(outfile);
      word[bit_index / 8] &= ~(1 << (bit_index % 8));
      bit_index++;
    }
  }

  uint8_t s = sym;                    
  uint8_t temp2 = 0;
  uint8_t s_length = (int)log2(s) + 1;    //check bits of current sym
  //set 1 or 0 to word array
  for (uint8_t i = 0; i < s_length; i++) {
    temp2 = (s & (1 << i));
    if (temp2) {
      buffer_check(outfile);
      word[bit_index / 8] |= 1 << (bit_index % 8);
      bit_index++;
    } else {
      buffer_check(outfile);
      word[bit_index / 8] &= ~(1 << (bit_index % 8));

      bit_index++;
    }
  }
  //bit shifts and place trailing 0
  for (uint8_t i = 0; i < 8 - s_length; i++) {
    buffer_check(outfile);
    word[bit_index / 8] &= ~(1 << (bit_index % 8));
    bit_index++;
  }
  //checks if reach BLOCK
  if (bit_index == BLOCK * 8) {
    flush_pairs(outfile);
    clear_words();
    bit_index=0;
  }
}

//writes out pairs
void flush_pairs(int outfile) {

  write(outfile, word, bit_index);   
  bit_index = 0;
}

bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  
  bitlen = (int)bitlen;
  //reads in BLOCK of bits
  if (bit_index == 0 || bit_index == BLOCK * 8) {
    bit_index = 0;
    int n = read(infile, buffer2, BLOCK);
    end = n;
    if (n == 0) {
      return false;
    }
  }

  uint16_t temp = 0;
  uint8_t array[1] ={0};	//array to store bits of char
  //puts 1 or 0 to array
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
    bit_index++;
  }
  *code = array[0];

  uint8_t temp2 = 0;
  uint8_t array2[1]= {0};	//array for sym
  //puts 1 or 0
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

    bit_index++;
    
  }
  *sym = array2[0];
  //if reaches end then break
  if (*code == STOP_CODE && *sym == 0) {
    return false;
  }
  
  return true;
}

//store each char at each index
void buffer_word(int outfile, Word *w) {

  if (d == BLOCK) {
    flush_words(outfile);
    d = 0;
  }
  for(uint64_t i=0;i<w->len;i++) {
    bufferd[d]=w->syms[i];
    d++;
  }
  
}

//write buffer out
void flush_words(int outfile) {  
  
  write(outfile,bufferd,d);
 
}

//checks if encoded bits buffer is full
void buffer_check(int outfile) {
  if (bit_index >= BLOCK * 8) {
    flush_pairs(outfile);
  }
}

//checks if decoded bits buffer is full
bool buffer2_check(int infile) {
  if (bit_index >= BLOCK * 8 || bit_index >= end * 8) {
    int n = read(infile, buffer2, BLOCK);
    end = n;
    bit_index = 0;
  }
  if (end == 0) {
    return false;
  }
  return true;
}

//reset word array?
void clear_words(void) {
  for (uint16_t i = 0; i < BLOCK; i++) {
    if (word[i]) {
      // free(words[i]);
      word[i / 8] &= ~(1 << (i % 8));
    }
  }
}

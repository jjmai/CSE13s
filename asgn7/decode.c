#include "code.h"
#include "io.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int infile;  // to read pairs form that is compressed
  int outfile; // output back to normal
  if (argc < 2) {
    infile = 0;
    outfile = 1;
  }

  int opt;
  int letter = 0;
  while ((opt = getopt(argc, argv, "vi:o:")) != EOF) {
    switch (opt) {
    case 'v':
      letter = 'v';
      break;
    case 'i':

      infile = open(optarg, O_RDONLY | O_CREAT);

      break;
    case 'o':
      outfile = open(optarg, O_WRONLY | O_CREAT);

      break;
    default:
      exit(1);
    }
  }
  //FileHeader *fh = (FileHeader *)malloc(sizeof(FileHeader));
 // read_header(infile , fh);

  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;
  while (read_pair(infile, &curr_code, &curr_sym, log2(next_code) + 1) ==
         true) {
    // printf("%d %d ",curr_code,curr_sym);
    table[next_code] = word_append_sym(table[curr_code], curr_sym);
    buffer_word(outfile, table[next_code]);
    // printf("%c ,%c ",curr_code , curr_sym);
    next_code += 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      next_code = START_CODE;
    }
  }
  flush_words(outfile);
  return 0;
}

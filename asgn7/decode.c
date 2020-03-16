#include "code.h"
#include "io.h"
#include "word.h"
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern double csize;
extern double dsize;

int main(int argc, char *argv[]) {
  int infile;
  int outfile;
  infile = STDIN_FILENO;
  outfile = STDOUT_FILENO;

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
      outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC);

      break;
    default:
      exit(1);
    }
  }
  FileHeader *fh = (FileHeader *)malloc(sizeof(FileHeader));
  read_header(infile, fh);

  WordTable *table = wt_create();
  uint8_t curr_sym = 0;
  uint16_t curr_code = 0;
  uint16_t next_code = START_CODE;

  while (read_pair(infile, &curr_code, &curr_sym, log2(next_code) + 1) ==
         true) {

    table[next_code] = word_append_sym(table[curr_code], curr_sym);

    buffer_word(outfile, table[next_code]);

    next_code += 1;
    if (next_code == MAX_CODE) {
      wt_reset(table);
      table = wt_create();
      next_code = START_CODE;
    }
  }
  flush_words(outfile);

  if (letter == 'v') {
    printf("\n");
    fprintf(stderr, "Compressed file size: %f bytes\n", csize);
    fprintf(stderr, "Uncompressed file size: %f bytes\n", dsize);
    fprintf(stderr, "Compression ratio: %f%s\n",
            100 * (1 - csize / dsize), "%");
  }
  wt_reset(table);
  free(table);
  free(fh);
  close(infile);
  close(outfile);
  return 0;
}

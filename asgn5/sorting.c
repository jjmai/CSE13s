#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_NUM 1073741823
#define srand_default 8222022

extern int moves;
extern int compare;
int printing();

int main(int argc, char *argv[]) {
  int opt;
  int *ptr;
  int index = 0, length = 0, s_number = 0, prints = 0;
  int let_index = 0;
  int letter[16];

  while ((opt = getopt(argc, argv, "Absqip:r:n:")) != -1) {
    switch (opt) {
    case 'A':
      letter[index] = 'A';
      index++;
      break;
    case 'b':
      letter[index] = 'b';
      index++;
      break;
    case 's':
      letter[index] = 's';
      index++;
      break;
    case 'q':
      letter[index] = 'q';
      index++;
      break;
    case 'i':
      letter[index] = 'i';
      index++;
      break;
    case 'p':
      prints = atoi(optarg);
      break;
    case 'r':
      s_number = atoi(optarg);
      break;
    case 'n':
      length = atoi(optarg);
      break;
    default:
      exit(1);
    }
  }
  letter[index] = '\0';
  if (prints == 0) {
    prints = 100;
  }
  if (s_number == 0) {
    s_number = srand_default;
  }
  if (length == 0) {
    length = 100;
  }
  ptr = (int *)calloc(length, sizeof(int));

  while (letter[let_index] != '\0') {
    int rando = 0;
    if (letter[let_index] == 'b' || letter[let_index] == 'A') {
      printf("Bubble Sort\n");
      printf("%d elements ", length);
      srand(s_number);
      for (int i = 0; i < length; i++) {
        rando = rand() & MAX_NUM;
        ptr[i] = rando;
      }
      bubble_sort(ptr, length);
      printing();
      for (int i = 0; i < prints && i < length; i++) {
        printf("\t%-10d",ptr[i]);
      }
      if (letter[let_index] != 'A') {
        let_index++;
      }
      printf("\n\n");
    }
    if (letter[let_index] == 's' || letter[let_index] == 'A') {
      printf("Shell Sort\n");
      printf("%d elements ", length);
      srand(s_number);
      for (int i = 0; i < length; i++) {
        rando = rand() & MAX_NUM;
        ptr[i] = rando;
      }
      shell_sort(ptr, length);
      printing();
      for (int i = 0; i < prints && i < length; i++) {
        printf("\t%-10d", ptr[i]);
      }
      if (letter[let_index] != 'A') {
        let_index++;
      }
      printf("\n\n");
    }
    if (letter[let_index] == 'q' || letter[let_index] == 'A') {
      printf("Quick Sort\n");
      printf("%d Elements ",length);
      srand(s_number);
      for (int i = 0; i < length; i++) {
        rando = rand() & MAX_NUM;
        ptr[i] = rando;
      }
      quick_sort(ptr, length, 0, length - 1);
      printing();
      for (int i = 0; i < prints && i < length; i++) {
        printf("\t%-10d", ptr[i]);
      }
      if (letter[let_index] != 'A') {
        let_index++;
      }
      printf("\n\n");
    }
    if (letter[let_index] == 'i' || letter[let_index] == 'A') {
      printf("Binary Insertion Sort\n");
      printf("%d Elements ",length);
      srand(s_number);
      for (int i = 0; i < length; i++) {
        rando = rand() & MAX_NUM;
        ptr[i] = rando;
      }
      binary_sort(ptr, length);
      printing();
      for (int i = 0; i < prints && i < length; i++) {
        printf("\t%-10d", ptr[i]);
      }
      if (letter[let_index] != 'A') {
        let_index++;
      }
      printf("\n\n");
      if(letter[let_index] == 'A') {
	let_index++;
}
    }
  }
  free(ptr);
  return 0;
}

int printing() {
  printf("%d moves ", moves);
  printf("%d comparisons ", compare);
  printf("\n");
  moves = 0;
  compare = 0;
  return 0;
}

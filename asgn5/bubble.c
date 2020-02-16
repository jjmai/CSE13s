#include "bubble.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int moves;
int compare;

int *bubble_sort(int ptr[], int length) {
  int j = 0;
  int swap;
  for (int i = 0; i < length - 1; i++) {
    j = length - 1;
    while (j > i) {
      if (ptr[j] < ptr[j - 1]) {
        swap = ptr[j];
        ptr[j] = ptr[j - 1];
        ptr[j - 1] = swap;
        moves += 3;
      }
      j -= 1;
      compare += 1;
    }
  }
  return 0;
}

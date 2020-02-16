#include "shell.h"
#include <stdio.h>
int gap();
int moves;
int compare;

int *shell_sort(int ptr[], int length) {
  int x = 0;
  int swap = 0;
  int temp_length = length;
  while (gap(temp_length) != 0) {
    x = gap(temp_length);
    for (int i = x; i < length; i++) {
      for (int j = i; j > x - 1; j -= x) {
        if (ptr[j] < ptr[j - x]) {
          swap = ptr[j];
          ptr[j] = ptr[j - x];
          ptr[j - x] = swap;
          moves += 3;
        }
        compare += 1;
      }
    }
    temp_length =x;
  }
  return 0;
}

int gap(int n) {
  if (n > 1) {
    if (n <= 2) {
      n = 1;
    } else {
      n = 5 * n / 11;
    }
    return n;
  }
  return 0;
}

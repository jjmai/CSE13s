#include "binary.h"
#include <stdio.h>

int moves;
int compare;

int *binary_sort(int ptr[], int length) {
  for (int i = 1; i < length; i++) {
    int value = ptr[i];
    int left = 0;
    int right = i;
    int swap = 0;
    while (left < right) {
      int mid = left + ((right - left) / 2);
      if (value >= ptr[mid]) {
        left = mid + 1;
      }
      compare+=1;

      if(value<ptr[mid]){
        right = mid;
      }
    }
    for (int j = i; j > left; --j) {
      swap = ptr[j];
      ptr[j] = ptr[j - 1];
      ptr[j - 1] = swap;
      moves += 3;
    }
  }
  return 0;
}

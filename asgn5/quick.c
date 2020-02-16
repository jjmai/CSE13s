#include "quick.h"
#include <stdbool.h>
#include <stdio.h>

int partition();
int moves;
int compare;

int *quick_sort(int ptr[], int length, int left, int right) {
  if (left < right) {
    int index = partition(ptr, left, right);
    compare+=1;
    quick_sort(ptr, length, left, index - 1);
    compare+=1;
    quick_sort(ptr, length, index + 1, right);
    compare+=1;
  }

  return 0;
}

int partition(int ptr[], int left, int right) {
  int pivot = ptr[left];
  int lo = left + 1;
  int hi = right;
  int swap = 0;
  
  while (true) {
    while (lo <= hi && ptr[hi] >= pivot) {
      hi -= 1;
      compare+=1;
    }
    while (lo <= hi && ptr[lo] <= pivot) {
      lo += 1;
      compare+=1;
    }
    if (lo <= hi) {
      swap = ptr[lo];
      ptr[lo] = ptr[hi];
      ptr[hi] = swap;
      moves += 3;
    }
    compare+=1; 
    if (lo > hi) {
      break;
}
    
  }
  swap = ptr[left];
  ptr[left] = ptr[hi];
  ptr[hi] = swap;
  moves += 3;

  return hi;
}

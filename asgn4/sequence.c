#include "bv.h"
#include "sieve.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int isPalindrome();
int fib();
int fib2();
int lucas();
int lucas2();
int mer();
int mer2();
char *convert();

int main(int argc, char *argv[]) {
  int opt;
  int num = 0;
  bool head = true; // to print headers
  int letter = 0;
  char array[36]; // array pointer to base conversion
  while ((opt = getopt(argc, argv, "spn:")) != EOF) {
    switch (opt) {
    // This case will direct to prime functions
    case 's':
      letter = 's';
      break;
    // This case will direct to palindome functions
    case 'p':
      letter = 'p';
      break;
    // This is max number to be printed
    case 'n':
      num = atoi(optarg);
      break;
    default:
      printf("ERROR");
      exit(1);
    }
  }
  if (num < 0) {
    printf("ERROR");
    exit(1);
  }
  if (num == 0) {
    num = 1000; // default 1000
  }
  BitVector *v = bv_create(num);
  sieve(v);
  if (letter == 's') {
    for (int j = 0; j <= num; j++) {
      if (bv_get_bit(v, j) == 1) {
        printf("%d: ", j);
        printf("prime");
        // checks if mersenne prime exist
        if (mer(j) == true) {
          printf(", mersenne");
        }
        // checks if luca prime exists
        if (lucas(j) == true) {
          printf(", lucas");
        }
        // check fibonacci prime
        if (fib(j) == true) {
          printf(", fibonacci");
        }
        printf("\n");
      }
    }
  }
  if (letter == 'p') {
    int base = 2;
    int count = 0;
    char string[36];
    // only tests 4 base conversion
    while (count != 4) {
      if (count == 1) {
        base = 10;
      } else if (count == 2) {
        base = 14;
      } else if (count == 3) {
        base = 23;
      }
      for (int k = 0; k <= num; k++) {
        if (bv_get_bit(v, k) == 1) {
          if (head == true) {
            printf("Base %d\n", base);
            printf("---- --\n");
            head = false;
          }
          convert(k, base, array);
          if (isPalindrome(array) == true) {
            printf("%d = ", k);
            printf("%s", array);
            printf("\n");
          }
        }
      }
      head = true;
      count += 1;
      printf("\n");
    }
  }
  bv_delete(v); // free space
  return 0;
}
// PROF DL
int isPalindrome(char prime[]) {
  if (prime == NULL) {
    return false;
  }
  int left = 0;
  int right = -1;
  // find length ofr array string
  for (int i = 0; prime[i] != '\0'; i++) {
    right += 1;
  }
  // checks if left most if = right most and increments to the middle
  while (left <= right) {
    if (prime[left] != prime[right]) {
      return false;
    }
    left += 1;
    right -= 1;
  }
  return true;
}

int fib(int n) {
  bool p;
  int check = 0;
  int j = 0;
  // continue while the returned fib number is less than the prime number input
  while (check <= n) {
    p = true;
    check = fib2(j);
    for (int i = 2; i < check; i++) {
      if (check % i == 0) { // checks if it is a prime number
        p = false;
      }
    }
    if (n == check && p != false) { // if the prime number is equal to fib
                                    // number
      return true;
    }
    j++; // checks terms
  }
  return false;
}
// fibonacci function
int fib2(int n) {
  int a = 0, b = 1, c;
  if (n <= 1) {
    return n;
  }
  for (int i = 2; i <= n; i++) {
    c = a + b;
    a = b;
    b = c;
  }
  return b; // returns the fib number at term number
}
// checks lucas
int lucas(int n) {
  bool p;
  int check = 0;
  int j = 0;
  while (check <= n) { // continue if lucas number is smaller than our prime #
    p = true;
    check = lucas2(j);
    for (int i = 2; i < check; i++) {
      if (check % i == 0) {
        p = false;
      }
    }
    if (n == check && p != false) {
      return true;
    }
    j++;
  }
  return false;
}
// returns lucas number at position
int lucas2(int n) {
  int a = 2, b = 1, c;
  if (n == 0) {
    return 2;
  }
  if (n == 1) {
    return 1;
  }
  for (int i = 2; i <= n; i++) {
    c = a + b;
    a = b;
    b = c;
  }
  return b; // return lucas number at the term number
}
// returns mersenne
int mer2(int n) {
  return (1 << n) - 1; // returns mersenne number at the term
}
// mersenne function
int mer(int n) {
  bool p;
  int check = 0;
  int j = 0;
  while (check <= n) { // continue while mersenne number is smaller than prime #
    p = true;
    check = mer2(j);
    for (int i = 2; i < check; i++) {
      if (check % i == 0) {
        p = false;
      }
    }
    if (n == check && p != false) {
      return true;
    }
    j++;
  }
  return false;
}
// This function converts a number to required base
// PROF DL
char *convert(int n, int base, char array[]) {
  int b = 0, i = 0;
  char a;
  int check = n;
  // PROFF DL
  static char fourteen[] = "0123456789ABCD";             // base 14
  static char twentythree[] = "0123456789ABCDEFGHIJKLM"; // base 23(M)
  while (check > 0) {
    a = check % base + '0'; // to store as a string
    if (base == 14) {
      array[i] = fourteen[check % 14];
    } else if (base == 23) {
      array[i] = twentythree[check % 23];
    } else {
      array[i] = a;
    }
    b = check / base;
    check = b;
    i++;
  }
  array[i] = '\0'; // Put NULL at end
  return array;    // returns pointer to array
}

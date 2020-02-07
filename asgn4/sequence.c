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
int *convert();

int main(int argc, char *argv[]) {
  int opt, num;
  int letter = 0;
  int *point;
  while ((opt = getopt(argc, argv, "spn:")) != EOF) {
    switch (opt) {
    case 's':
      letter = 's';
      break;

    case 'p':
      letter = 'p';
      break;

    case 'n':
      num = atoi(optarg);
      break;
    default:
      printf("ERROR");
      exit(1);
    }
  }
  BitVector *v = bv_create(num);
  sieve(v);
  if (letter == 's') {
    for (int j = 0; j <= num; j++) {
      if (bv_get_bit(v, j) == 1) {
        printf("%d: ", j);
        printf("prime");
        if (mer(j) == true) {
          printf(", mersenne");
        }
        if (lucas(j) == true) {
          printf(", lucas");
        }
        if (fib(j) == true) {
          printf(", fibonacci");
        }
        printf("\n");
      }
    }
  }
  return 0;
}

int isPalindrome(char prime[]) {
  int left = 0;
  int right = -1;
  for (int i = 0; prime[i] != '\0'; i++) {
    right += 1;
  }
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
  bool p = true;
  int check = 0;
  for (int i = 0; i <= 20; i++) {
    p = true;
    check = fib2(i);

    for (int i = 2; i < check; i++) {
      if (check % i == 0 && check != 2) {
        p = false;
      }
    }
    if (n == check && p != false) {
      return true;
    }
  }
  return false;
}
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
  return b;
}

int lucas(int n) {
  bool p = true;
  int check = 0;
  for (int i = 0; i <= 20; i++) {
    p = true;
    check = lucas2(i);
    for (int i = 2; i < check; i++) {
      if (check % i == 0 && check != 2) {
        p = false;
      }
    }
    if (n == check && p != false) {
      return true;
    }
  }
  return false;
}

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
  return b;
}

int mer2(int n) { return pow(2, n) - 1; }

int mer(int n) {
  bool p = true;
  int check = 0;
  for (int i = 0; i <= 20; i++) {
    p = true;
    check = mer2(i);
    for (int i = 2; i < check; i++) {
      if (check % i == 0 && check != 2) {
        p = false;
      }
    }
    if (n == check && p != false) {
      return true;
    }
  }
  return false;
}

int *convert(int n, int base) {
  int a = 0, b = 0, i = 0;
  int answer = 0;
  int check = n;
  static int array[36];
  char string[100];
  char string2[100];
  while (check > 0) {
    a = check % base;
    array[i] = a;
    b = check / base;
    check = b;
    i++;
  }
  array[i] = '\0';
  return array;
}

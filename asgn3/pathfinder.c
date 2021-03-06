#include "stack.h"
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 26
#define HEIGHT 26

void Head();
void Maze();
int checki = 0, checkj = 0;
int test = 0;
int temp = 100;
int length = 0;
int amount = 0;
char letter = 0;
int visited[26]; // 2d array to mark down areas checked
int grid[26][26];


int main(int argc, char **argv) {
  Stack *s = stack_create();
  FILE *fp = stdin;
  int opt;
  int answer = 0, answer2 = 0;
  int i, j, x = 0, y = 0;
  char c = 'A';
  char ch[256];
  bool check = false;
  // CREATES a 2d ARRAY
  for (i = 0; i < WIDTH; i++) {
    visited[i] = 0;
    for (j = 0; j < HEIGHT; j++) {
      grid[i][j] = 0;
    }
  }
  while ((opt = getopt(argc, argv, "i:udm")) != -1) {
    switch (opt) {
    // PROF DL
    case ('i'):
      letter = 'i';
      fp = fopen(optarg, "r");
      if (fp == NULL) {
        exit(1);
      }

    case ('u'):
      letter = 'u';
      while (fscanf(fp, "%s", ch) != EOF) {
        // Take in input and convert to numbers
        answer = ch[0] - 'A';
        answer2 = ch[1] - 'A';
        // change lowercase to upper
        if (answer > 30) {
          answer -= 32;
        }
        if (answer2 > 30) {
          answer2 -= 32;
        }

        if (check != true) {
          x = answer;
          // y = answer2;
          check = true;
          visited[x] = 1;
        }
        grid[answer][answer2] = 1;
        grid[answer2][answer] = 1;
      }

      break;
    case ('d'):
      if (letter != 'u') {
        letter = 'd';
        while (fscanf(fp, "%s", ch) != EOF) {
          answer = ch[0] - 'A';
          answer2 = ch[1] - 'A';
          if (answer > 30) {
            answer -= 32;
          }
          if (answer2 > 30) {
            answer2 -= 32;
          }
          if (check != true) {
            x = answer;
            check = true;
            visited[x] = 1;
          }
          grid[answer][answer2] = 1;
        }
      }
      break;

    case ('m'):
      Head();
      // print output
      for (i = 0; i < 26; i++) {
        printf("%c ", c++);
        for (j = 0; j < 26; j++) {
          printf("%d ", grid[i][j]);
        }
        printf("\n");
      }
      break;
    default:
      exit(1);
    }
  }
  //stack_push(s, 0);
  Maze(s,0);
  printf("Number of paths: %d\n", amount);
  printf("Length of shortest path is: %d\n", temp);
}

// header
void Head(void) {
  char c = 'A';
  int i = 0;
  printf("  ");
  for (i = 0; i < 26; i++) {
    printf("%c ", c++);
  }
  printf("\n");
}

// recursion
void Maze(Stack *s, int y) {
  // goes in if end is reached
  if (y == 25) {
    stack_push(s, y);
    stack_print(s);
    amount++;            // how many paths
    if (s->top < temp) { // shortest length
      temp = s->top;
    }
    stack_pop(s, s->items);
    return;
  }
  visited[y] = 1;
  for (int i = 0; i < 26; i++) {
    if (grid[y][i] == 1 && visited[i] != 1) {
      stack_push(s, y);
      visited[i] = 1;
      Maze(s, i);
      stack_pop(s, s->items);
      visited[i] = 0;
    }
  }
  return;
}

#include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//PROF DL
Stack *stack_create(void) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  if (!s) {
    exit(-1);
  }
  s->capacity = MINIMUM;
  s->top = 0;

  s->items = (item *)malloc(s->capacity * sizeof(item));
  return s;
}

void stack_delete(Stack *s) { free(s); }
bool stack_empty(Stack *s) { return s->top = 0; }

uint32_t stack_size(Stack *s) { return s->top; }
bool stack_push(Stack *s, item i) {
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (item *)realloc(s->items, s->capacity * sizeof(item));
  }
  s->items[s->top] = i;

  s->top += 1;

  return true;
}

bool stack_pop(Stack *s, item *i) {
  if (stack_empty(s) == 0) {
    return false;
  }
  s->top -= 1;
  *i = s->items[s->top];
  return true;
}

void stack_print(Stack *s) {
  char c;
  int temp = 0;
  temp = s->top;
  s->top = 0;
  while (s->top != temp) {
    c = s->items[s->top] + 'A';
    printf("%c", c);
    if (c != 'Z') {
      printf("->");
    }
    s->top++;
  }
  printf("\n");
}

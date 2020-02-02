#ifndef __STACK_H__
#define __STACK_H__
#include <inttypes.h>
#include <stdbool.h>

#define MINIMUM 26
typedef uint32_t item;

typedef struct Stack {
  item *items;       // A stack holds uint32_t .
  uint32_t top;      // Keeps track of the top index of a stack .
  uint32_t capacity; // Keeps track of a stack ’s capacity .
} Stack;

Stack *stack_create(void);

void stack_delete(Stack *s);

bool stack_empty(Stack *s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, item i);

bool stack_pop(Stack *s, item *i);

void stack_print(Stack *s);

#endif

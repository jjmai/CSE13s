#include "word.h"
#include "code.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint64_t len) {
  Word *ww = (Word *)malloc(sizeof(Word));
  assert(ww);
  ww->syms = calloc(len, sizeof(Word)); //allocate space equal to syms
  assert(ww->syms);
  ww->len = len;
  // copies syms over to newly created Word
  for (uint64_t i = 0; i < ww->len; i++) {
    ww->syms[i] = syms[i];
  }
  return ww;
}

Word *word_append_sym(Word *w, uint8_t sym) {
  // if table is empty, just create the word
  if (w == NULL) {
    Word *ww = word_create(&sym, sizeof(sym));
    ww->syms[ww->len - 1] = sym;
    return ww;
  }
  Word *ww = word_create(w->syms, w->len + 1); // create with one extra spot
  ww->syms[ww->len - 1] = sym;                 // places at last index of Word
  return ww;
}

WordTable *wt_create(void) {
  WordTable *w = (WordTable *)calloc(MAX_CODE, sizeof(WordTable));
  assert(w);
  w[EMPTY_CODE] = word_create(NULL, 0);

  return w;
}

void wt_reset(WordTable *wt) {
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i]) {
      wt_delete(&wt[i]);
      wt[i] = NULL;
    }
  }

  wt[EMPTY_CODE] = word_create(NULL, 0);
}

void wt_delete(WordTable *wt) {
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i]) {
      free(wt[i]);
      wt[i] = NULL;
    }
  }
}

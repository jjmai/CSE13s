#include "word.h"
#include "code.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Word *word_create(uint8_t *syms, uint64_t len) {
  Word *ww = (Word *)malloc(sizeof(Word));
  ww->syms = calloc(len, sizeof(Word));
  ww->len=len;
  //memcpy(ww->syms, &syms, ww->len);
  //printf("%s !",ww->syms);
  for(uint64_t i=0;i<ww->len;i++) {
    ww->syms[i]=syms[i];
  }
  printf("%s ",ww->syms);  
  return ww;
}

Word *word_append_sym(Word *w, uint8_t sym) {
  //printf("%c--\n",sym);
  if (w == NULL) {    
    Word *ww = word_create(&sym, sizeof(sym));
    ww->syms[ww->len-1]=sym;
    return ww;
  }
  Word *ww = word_create(w->syms, w->len+1);
  ww->syms[ww->len - 1] = sym;
  // printf("%s !",ww->syms);
  return ww;
}

WordTable *wt_create(void) {
  WordTable *w = (WordTable *)calloc(MAX_CODE, sizeof(WordTable));
  
  w[EMPTY_CODE] = word_create(NULL, 0);

  return w;
}

void wt_reset(WordTable *wt) {
  wt_delete(wt);
  wt[EMPTY_CODE] = word_create(NULL, 0);
}

void wt_delete(WordTable *wt) {
  for (int i = 0; i < MAX_CODE; i++) {
    if (wt[i]) {
      free(wt[i]->syms);
      wt[i] = NULL;
    }
  }
}

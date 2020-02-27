#include "gs.h"
#include <stdlib.h>

GoodSpeak *gs_create(char *oldspeak, char *newspeak) {
  GoodSpeak *gs = (GoodSpeak *)malloc(sizeof(GoodSpeak));
  char *temp=strdup(oldspeak);
  char *temp2=strdup(newspeak);
  gs->oldspeak=temp;
  gs->newspeak=temp2;
  return gs;
}

void gs_delete(GoodSpeak *g) {
  free(g->oldspeak);
  free(g->newspeak);
  free(g);
}

char *gs_oldspeak(GoodSpeak *g) { return g->oldspeak; }

char *gs_newspeak(GoodSpeak *g) { return g->newspeak; }

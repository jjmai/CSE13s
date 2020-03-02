#include "gs.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//Creates a goodspeak struct for oldspeak and newspeak words
GoodSpeak *gs_create(char *oldspeak, char *newspeak) {
  GoodSpeak *gs = (GoodSpeak *)malloc(sizeof(GoodSpeak));
  if (oldspeak != NULL) {
    char *temp = malloc(strlen(oldspeak) + 1);
    gs->oldspeak = malloc(strlen(oldspeak) + 1);
    strcpy(temp, oldspeak);
    gs->oldspeak = temp;
  }
  if (newspeak != NULL) {
    char *temp2 = malloc(strlen(newspeak) + 1);
    gs->newspeak = malloc(strlen(newspeak) + 1);
    strcpy(temp2, newspeak);
    gs->newspeak = temp2;
  } else {
    gs->newspeak = NULL;
  }
  return gs;
}
//deletes goodspeak struct
void gs_delete(GoodSpeak *g) {
  free(g->oldspeak);
  free(g->newspeak);
  free(g);
}

char *gs_oldspeak(GoodSpeak *g) { return g->oldspeak; }

char *gs_newspeak(GoodSpeak *g) { return g->newspeak; }

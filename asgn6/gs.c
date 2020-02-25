#include "gs.h"
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>

GoodSpeak *gs_create(char *oldspeak, char *newspeak){
    GoodSpeak *gs= (GoodSpeak *)malloc(sizeof(GoodSpeak));
    gs->oldspeak=oldspeak;
    gs->newspeak=newspeak;

    return gs;
}

void gs_delete(GoodSpeak *g){

}

char *gs_oldspeak(GoodSpeak *g){
    return g->oldspeak;

}

char *gs_newspeak(GoodSpeak *g){
    return g->newspeak;
}



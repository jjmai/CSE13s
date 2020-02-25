# include "hash.h"
# include "ll.h"
# include <inttypes.h>
# include <stdlib.h>
#include <string.h>
#include "speck.h"
#include <stdio.h>


HashTable * ht_create ( uint32_t length ) {
    HashTable *ht = ( HashTable *) malloc ( sizeof ( HashTable ) ) ;
    if (ht) {
        ht->salt[0] = 0x85ae998311115ae3 ; // Il nome della rosa
        ht->salt[1] = 0xb6fac2ae33a40089 ;
        ht->length = length ;
        ht->heads = ( ListNode **) calloc ( length , sizeof ( ListNode *) );
        return ht;
        }

    return ( HashTable *) NIL ;
    }


 void ht_delete ( HashTable *ht) {
    ListNode *temp;
    for(uint32_t i=0;i<ht->length;i++) {
        while(ht->heads !=NIL) {
            temp=ht->heads[i]=NIL;
            free(ht->heads[i]->gs);
            free(ht->heads[i]);
            ht->heads[i]=temp;
        }
        free(ht->heads[i]);
    }
    free(ht->heads);
}

ListNode * ht_lookup ( HashTable *ht , char * key )  {
    uint32_t h=hash(ht->salt,key)%ht->length;
    ll_lookup(&ht->heads[h],key);
    return ht->heads[h];
}
void ht_insert ( HashTable *ht , GoodSpeak *gs)  {

    uint32_t h=hash(ht->salt,gs->oldspeak)%ht->length;
    ht->heads[h]=ll_insert(&ht->heads[h],gs);

}

void ht_print(HashTable *h) {
    if (h) {
        for(int i=0;i<h->length;i++) {
            if(h->heads[i]!=NIL) {
                printf("%d\n",i);
            }

        }
    }
}


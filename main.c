#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hashMap.h"

/*
 the getWord function takes a FILE pointer and returns you a string which was
 the next word in the in the file. words are defined (by this function) to be
 characters or numbers seperated by periods, spaces, or newlines.

 when there are no more words in the input file this function will return NULL.

 this function will malloc some memory for the char* it returns. it is your job
 to free this memory when you no longer need it.
 */
char* getWord(FILE *file); /* prototype */

/****************************************/

int main (int argc, const char * argv[]) {
    /*Write this function*/
    hashMap *m;
    /*
    char* nextWord;
    FILE *file;
    int *val;
    */

    m = (hashMap*)malloc(sizeof(hashMap));
    assert(m != NULL);
    initMap(m, 10000);
    printf("Couldn't figure main out, see commented code for attempt.\n");

    /*
    file = fopen("input.txt", "r");
    assert(file != NULL);

    nextWord = getWord(file);
    while(nextWord != NULL) {
        val = atMap(m, nextWord);
        if(val == NULL) {
            insertMap(m, nextWord, 0);
        } else {
            insertMap(m, nextWord, ++(*val));
            printf("%s: ", nextWord);
            printf("%d\n", *val);
        }
        free(nextWord);
        nextWord = getWord(file);
    }
    */

    freeMap(m);
    free(m);
}

char *getWord(FILE *file) {
    char *word;

    word = (char*)malloc(sizeof(char) * 1024);
    assert(word != NULL);

    if(fscanf(file, " %1023s", word) != 0) {
        puts(word);
        return word;
    }

    return NULL;
}

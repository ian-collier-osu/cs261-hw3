#include <stdlib.h>
#include "hashMap.h"
#include "structs.h"
#include <string.h>
#include <assert.h>

#if HASHING_FUNCTION == 2
	#define HASHFUNC stringHash2
#else
	#define HASHFUNC stringHash1
#endif

int stringHash1(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += str[i];
	return r;
}

int stringHash2(char * str)
{
	int i;
	int r = 0;
	for (i = 0; str[i] != '\0'; i++)
		r += (i+1) * str[i]; /*the difference between 1 and 2 is on this line*/
	return r;
}

void initMap (struct hashMap * ht, int tableSize)
{
	int index;
	if(ht == NULL)
		return;
	ht->table = (hashLink**)malloc(sizeof(hashLink*) * tableSize);
	ht->tableSize = tableSize;
	ht->count = 0;
	for(index = 0; index < tableSize; index++)
		ht->table[index] = NULL;
}

void freeMap (struct hashMap * ht)
{  /*write this*/
	int i;
	struct hashLink *curLink, *prevLink;

	assert(ht != NULL);

	for(i = 0; i < ht->tableSize; ++i) {
		curLink = ht->table[i];
		prevLink = curLink;
		while(curLink != NULL) {
			prevLink = curLink;
			curLink = curLink->next;
			free(prevLink);
		}
	}
	free(ht->table);
}

void insertMap (struct hashMap * ht, KeyType k, ValueType v)
{  /*write this*/
	int hash, hashIndex;
	struct hashLink *newLink;

	assert(ht != NULL);

	hash = HASHFUNC(k);

	hashIndex = (int) (labs(hash) % ht->tableSize);

	newLink = (struct hashLink *) malloc(sizeof(struct hashLink));
	assert(newLink);

	newLink->value = v;
	newLink->next = ht->table[hashIndex];

	ht->table[hashIndex] = newLink;
	ht->count++;
}

ValueType* atMap (struct hashMap * ht, KeyType k)
{ /*write this?*/
	int hash, hashIndex;
	struct hashLink *cur;

	assert(ht != NULL);

	hash = HASHFUNC(k);
	hashIndex = (int) (labs(hash) % ht->tableSize);

	cur = ht->table[hashIndex];
	while(cur != NULL) {
		if(cur->key == k) return &(cur->value);
		cur = cur->next;
	}
	return NULL;
}

int containsKey (struct hashMap * ht, KeyType k)
{  /*write this*/
	assert(ht != NULL);

	return (atMap(ht, k) != NULL);
}

void removeKey (struct hashMap * ht, KeyType k)
{  /*write this?*/
	int hash, hashIndex;
	struct hashLink *cur, *last;

	assert(ht != NULL);

	hash = HASHFUNC(k);
	hashIndex = (int) (labs(hash) % ht->tableSize);

	cur = ht->table[hashIndex];
	last = ht->table[hashIndex];

	while(cur != NULL) {
		if(cur->key == k){
			if(cur == ht->table[hashIndex]) {
				ht->table[hashIndex] = cur->next;
			} else {
				last->next = cur->next;
			}
			free(cur);
			cur = NULL;
			ht->count--;
		} else {
			last = cur;
			cur = cur->next;
		}
	}
}

int sizeMap (struct hashMap *ht)
{  /*write this*/
	assert(ht != NULL);

	return ht->count;
}

int capacityMap(struct hashMap *ht)
{  /*write this*/
	assert(ht != NULL);

	return ht->tableSize;
}

int emptyBuckets(struct hashMap *ht)
{  /*write this*/
	int i, bucketCount;

	assert(ht != NULL);

	bucketCount = 0;
	for(i = 0; i < ht->tableSize; ++i) {
		if(ht->table[i] == NULL) ++bucketCount;
	}

	return bucketCount;
}

float tableLoad(struct hashMap *ht)
{  /*write this*/
	assert(ht != NULL);
	return 0;
}

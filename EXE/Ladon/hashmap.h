#ifndef HASHMAP_H
#define HASHMAP_H

#include "WindowsIAT.h"
#include "linked_list.h"

typedef struct hashmap_entry_t
{
	char *key;
	void *value;
} hashmap_entry_t;

typedef struct hashmap_t
{
	list_t *buckets;
	size_t nbuckets;
} hashmap_t;

hashmap_t *hashmap_new(size_t nbuckets);
void hashmap_free(hashmap_t *map);
BOOL hashmap_put(hashmap_t *map, char *key, void *value);
void *hashmap_get(hashmap_t *map, char *key, void *default_);

#endif /* HASHMAP_H */
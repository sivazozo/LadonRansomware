#include "ladon.h"

hashmap_t *
hashmap_new(size_t nbuckets)
{
	hashmap_t *map;

	map = (hashmap_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*map));
	if (map == NULL)
		return NULL;

	map->buckets = (list_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*map->buckets) * nbuckets);
	if (map->buckets == NULL)
	{
		_HeapFree(_GetProcessHeap(), 0, map);
		return NULL;
	}

	map->nbuckets = nbuckets;

	for (size_t i = 0; i < nbuckets; i++)
		map->buckets[i] = list_new();

	return map;
}

void
hashmap_free(hashmap_t *map)
{
	list_item_t *temp;

	for (size_t i = 0; i < map->nbuckets; i++)
	{
		for (temp = map->buckets[i].head; temp; temp = temp->next)
		{
			_HeapFree(_GetProcessHeap(), 0, ((hashmap_entry_t *)temp->value)->key);
			_HeapFree(_GetProcessHeap(), 0, temp->value);
		}

		list_free(&map->buckets[i]);
	}

	_HeapFree(_GetProcessHeap(), 0, map->buckets);
}

static size_t
hashmap_hash(hashmap_t *map, char *key)
{
	size_t hash = 5381;

	for (; *key != '\0'; key++) /* djb2 hashing algorithm */
		hash = (size_t)*key + (hash << 5) + hash;

	return hash % map->nbuckets;
}

BOOL
hashmap_put(hashmap_t *map, char *key, void *value)
{
	size_t addr;
	char *key_clone;
	hashmap_entry_t *entry;

	entry = (hashmap_entry_t*)_HeapAlloc(_GetProcessHeap(), 0, sizeof(*entry));
	if (!entry)
		return false;

	key_clone = (char*)_HeapAlloc(_GetProcessHeap(), 0, lstrlen(key) + 1);
	if (!key_clone)
	{
		_HeapFree(_GetProcessHeap(), 0, entry);
		return false;
	}

	zstrncpy(key_clone, key, lstrlen(key) + 1);

	entry->key = key_clone;
	entry->value = value;

	addr = hashmap_hash(map, key);

	return list_put(&map->buckets[addr], entry);
}

void *
hashmap_get(hashmap_t *map, char *key, void *default_)
{
	size_t addr = hashmap_hash(map, key);
	list_item_t *temp;

	for (temp = map->buckets[addr].head; temp; temp = temp->next)
	{
		if (lstrcmp(key, ((hashmap_entry_t *)temp->value)->key) == 0)
			return ((hashmap_entry_t *)temp->value)->value;
	}

	return default_;
}
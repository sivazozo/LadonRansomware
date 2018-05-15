#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "WindowsIAT.h"

typedef
struct list_item_t
{
	struct list_item_t *next;
	void *value;
} list_item_t;

typedef
struct list_t
{
	struct list_item_t *head;
} list_t;

list_t list_new();
void list_free(list_t *l);
BOOL list_put(list_t *l, void *value);

#endif /* LINKED_LIST_H */
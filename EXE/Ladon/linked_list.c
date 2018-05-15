#include "ladon.h"

list_t
list_new()
{
	list_t l;
	l.head = NULL;
	return l;
}

void
list_free(list_t *l)
{
	list_item_t *curr, *next;

	for (curr = l->head, next = ((curr != NULL) ? curr->next : NULL)
		; curr != NULL; curr = next, next = curr ? curr->next : NULL)
		_HeapFree(_GetProcessHeap(), 0, curr);
}

BOOL list_put(list_t *l, void *value)
{
	list_item_t *temp = l->head, *node;

	node = (list_item_t*)_HeapAlloc(_GetProcessHeap(), 0, (sizeof(*node)));
	if (node == NULL)
		return FALSE;

	node->value = value;
	node->next = NULL;

	if (l->head == NULL)
		l->head = node;
	else
	{
		for (; temp->next; temp = temp->next);
		temp->next = node;
	}

	return TRUE;
}
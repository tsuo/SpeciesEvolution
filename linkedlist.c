#include <stdlib.h>
#include <stdio.h>

#include "xmalloc.h"
#include "linkedlist.h"

conscell *ll_push(conscell *list, void *data)
{
	conscell *new = xmalloc(sizeof *new);
	new->data = data;
	new->next = list;
	return new;
}
conscell *ll_pop(conscell *list)
{
	if(list == NULL) return NULL;

	conscell *p = list->next;
	free(list);
	return p;
}

void ll_free(conscell *list)
{
	while(list != NULL)
	{
		list = ll_pop(list);
	}
}

// not implemented
conscell *ll_reverse(conscell *list)
{
	return NULL;	
}

conscell *ll_sort(conscell *list,
		int (*cmp)(const void *a, const void *b, void *params),
		void *params)
{
	conscell *list1 = NULL;
	conscell *list2 = NULL;
	conscell *p, *q, *head;
	if(list == NULL)
		return list;
	head = list;
	p = list->next;
	while(p != NULL) {
		q = p->next;
		if(cmp(p->data, head->data, params) < 0) {
			p->next = list1;
			list1 = p;
		} else {
			p->next = list2;
			list2 = p;
		}
		p = q;
	}
	list1 = ll_sort(list1, cmp, params);
	list2 = ll_sort(list2, cmp, params);
	head->next = list2;
		
	if(list1 == NULL)
		return head;
	
	for(p = list1; p->next != NULL; p = p->next)
		;

	p->next = head;
	return list1;
}

conscell *ll_filter(conscell *list,
		int (*filter)(const void *a),
		conscell **removed)
{
	if(list == NULL)
		return list;
	else if(filter(list->data)) {
		conscell *p = list->next;
		list->next = *removed;
		*removed = list;
		return ll_filter(p, filter, removed);
	}else {
		list->next = ll_filter(list->next, filter, removed);
		return list;
	}
	
}

int ll_length(conscell *list)
{
	if(list == NULL) return 0;

	int count = 1;
	conscell *p = list;
	for(p = list; p->next != NULL; p=p->next, count++)
		;

	return count;
}


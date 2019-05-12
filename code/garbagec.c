#include <stdio.h>
#include <stdlib.h>


typedef struct Trash_t
{
	void *data;
	struct Trash_t *next;
}Trash;

static Trash *garbageCollector = NULL;

void *gcmalloc(const size_t sizeAlloc)
{
	Trash *temp = NULL;
	void *alloc = malloc(sizeAlloc);
	if(!alloc)
		return NULL;
	temp = malloc(sizeof(Trash));
	if(!temp)
		return NULL;
	temp->next = garbageCollector;
	temp->data = alloc;
	garbageCollector = temp;
	
	return alloc;
}

void *gccalloc(const size_t sizeAlloc, const int n)
{
	Trash *temp = NULL;
	void *alloc = calloc(sizeAlloc, n);
	if(!alloc)
		return NULL;
	temp = malloc(sizeof(Trash));
	if(!temp)
		return NULL;
	temp->next = garbageCollector;
	temp->data = alloc;
	garbageCollector = temp;
	
	return alloc;
}

void gcfree(void *gpointer)
{
	Trash *temp = garbageCollector, *temp2=NULL;
	if(!temp)
		return;
	if(temp->data == gpointer)
	{
		free(gpointer);
		free(temp);
		garbageCollector = temp->next;
		return;
	}
	temp2 = temp;
	temp = temp->next;
	while(temp)
	{
		if(temp->data == gpointer)
		{
			temp2->next = temp->next;
			free(gpointer);
			free(temp);
			return;
		}
		temp2 = temp;
		temp = temp->next;
	}
}

void gcclear(void)
{
	Trash *temp = garbageCollector;
	while(temp)
	{
		garbageCollector = temp->next;
		free(temp->data);
		free(temp);
		temp = garbageCollector;
	}
}

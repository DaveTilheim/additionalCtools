#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionnary.h"

typedef struct Dict
{
	void **values;
	char **keys;
	unsigned maxelement;
	unsigned nbKeys;
}Dict;

Dict *new_dict(const int maxelement)
{
	if(maxelement <= 0)
		return NULL;
	Dict *dict = malloc(sizeof(Dict));
	if(!dict)
		return dict;
	dict->maxelement = maxelement;
	dict->nbKeys = 0;
	dict->values = malloc(sizeof(void *)*maxelement);
	if(!dict->values)
	{
		free(dict);
		return NULL;
	}
	dict->keys = malloc(sizeof(char *)*maxelement);
	if(!dict->keys)
	{
		free(dict->values);
		free(dict);
		return NULL;
	}

	return dict;
}

void set_dict(Dict *dict, const char *key, void *data)
{
	int i;
	for(i = 0; i < dict->nbKeys; i++)
	{
		if(!strcmp(dict->keys[i], key))
		{
			dict->values[i] = data;
			return;
		}
	}
	if(i < dict->maxelement)
	{
		dict->keys[i] = malloc(sizeof(char)*strlen(key)+1);
		if(!dict->keys[i])
		{
			fprintf(stderr, "dict allocation error\n");
			return;
		}
		strcpy(dict->keys[i], key);
		dict->values[i] = data;
		dict->nbKeys++;
	}
	
}

void *get_dict(Dict *dict, const char *key)
{
	for(int i = 0; i < dict->nbKeys; i++)
		if(!strcmp(dict->keys[i], key))
			return dict->values[i];
	return NULL;
}

Dict *free_dict(Dict *dict)
{
	if(dict)
	{
		if(dict->values)
			free(dict->values);
		if(dict->keys)
		{
			for(int i = 0; i < dict->nbKeys; i++)
			{
				if(dict->keys[i])
					free(dict->keys[i]);
			}
			free(dict->keys);
		}
		free(dict);
	}

	return NULL;
}






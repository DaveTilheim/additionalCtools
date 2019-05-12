#ifndef __DICTIONNARY__
#define __DICTIONNARY__

typedef struct Dict Dict;

Dict *new_dict(const int);
void set_dict(Dict *, const char *, void *);
void *get_dict(Dict *, const char *);
Dict *free_dict(Dict *);

#endif

#ifndef __GARBAGEC_H__
#define __GARBAGEC_H__


void *gcmalloc(const size_t);
void *gccalloc(const size_t, const int);
void gcfree(void *);
void gcclear(void);


#endif

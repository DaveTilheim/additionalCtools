#ifndef __GENERIC__
#define __GENERIC__

#define __no_nul_return
#define __nul_return
#define gcmpcast(fname) (int (*)(const void *, const void *))fname
#define gget(gptr, type) *(type*)gptr
#define gset(gptr, type, value) *(type*)gptr = value 

void gswap(void *, void *, const size_t);
void gheapsort(void *, unsigned long, const size_t, int __no_nul_return (*)(const void*, const void*));
int gseqsearch(const void *, const void *, const int, const size_t, int __nul_return (*)(const void*,const void*));
int gdsearch(const void *, const void *, const int, const size_t, int __nul_return (*)(const void*,const void*));
void gheapsort_b(void *, unsigned long, const size_t, int __no_nul_return (^)(const void*, const void*));
int gseqsearch_b(const void *, const void *, const int, const size_t, int __nul_return (^)(const void*,const void*));
int gdsearch_b(const void *, const void *, const int, const size_t, int __nul_return (^)(const void*,const void*));

#define type(var) _Generic(var,\
	char:"char", unsigned char:"unsigned char", short:"short",unsigned short:"unsigned short",\
	int:"int",unsigned:"unsigned",long:"long",unsigned long:"unsigned long",\
	float:"float",double:"double",void *:"void *",char *:"char *",unsigned char *:"unsigned char *",\
	short *:"short *",unsigned short *:"unsigned short *", int *:"int *",unsigned *:"unsigned *",\
	long *:"long *", unsigned long *:"unsigned long *",\
	float *:"float *", double *:"double *",\
	FILE:"FILE", FILE *:"FILE *",\
	default: "none"\
)
#include <string.h>
#define is(var, typeName) !strcmp(type(var), typeName)
#define print(var) __gprint(&var, type(var))

void __gprint(void *, char *);

#endif

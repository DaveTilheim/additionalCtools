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

#endif

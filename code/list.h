#ifndef __LIST__
#define __LIST__

#define _implicit_alloc_data
#define _implicit_free_data

#ifdef MEMORY_VIEW_DEBUG
void viewMemWatches(void);
#endif
struct List_t
{
	void *data;
	struct List_t *next;
};
typedef struct List_t List, *pList;
typedef struct List_t Cell;


unsigned long len_list(List*);
int is_empty_list(List *);
List *empty_list(void);
List *new_list(unsigned long, ...);
List *add_first(List *, void*);
List *add_last(List *, void*);
List *add_at(List *, void*, unsigned long);
List *add_nfirst(List *, unsigned long, ...);
List *add_nlast(List *, unsigned long, ...);
List *add_nat(List *, unsigned long, unsigned long, ...);
List *_implicit_alloc_data new_listcpy(size_t, unsigned long,  ...);
List *_implicit_alloc_data add_cpyfirst(List *, size_t, void*);
List *_implicit_alloc_data add_cpylast(List *, size_t, void*);
List *_implicit_alloc_data add_cpyat(List *, size_t, void*, unsigned long);
List *_implicit_alloc_data add_ncpyfirst(List *, size_t, unsigned long, ...);
List *_implicit_alloc_data add_ncpylast(List *, size_t, unsigned long, ...);
List *_implicit_alloc_data add_ncpyat(List *, size_t, unsigned long, unsigned long, ...);
void _implicit_alloc_data set_cpyfirst(List *, size_t, void *);
void _implicit_alloc_data set_cpylast(List *, size_t, void *);
void _implicit_alloc_data set_cpyat(List *L, size_t, unsigned long i, void *data);
void _implicit_alloc_data _implicit_free_data setd_cpyfirst(List *, size_t, void *);
void _implicit_alloc_data _implicit_free_data setd_cpylast(List *, size_t, void *);
void _implicit_alloc_data _implicit_free_data setd_cpyat(List *L, size_t, unsigned long i, void *data);
void set_first(List *, void *);
void set_last(List *, void *);
void set_at(List *L, unsigned long i, void *data);
void _implicit_free_data setd_first(List *, void *);
void _implicit_free_data setd_last(List *, void *);
void _implicit_free_data setd_at(List *, unsigned long, void *);
List *_implicit_alloc_data add_int(List *, long);
List *_implicit_alloc_data add_nint(List *, unsigned long, ...);
List *_implicit_alloc_data add_double(List *, double);
List *_implicit_alloc_data add_ndouble(List *, unsigned long, ...);
List *_implicit_alloc_data add_str(List *, char *);
List *_implicit_alloc_data add_nstr(List *, unsigned long, ...);
void *get_first(List *);
void *get_last(List *);
void *get_at(List *, unsigned long);
List *free_first(List *);
List *free_last(List *);
List *free_at(List *, unsigned long);
List *free_list(List*);
List *_implicit_free_data freed_first(List *);
List *_implicit_free_data freed_last(List *);
List *_implicit_free_data freed_at(List *, unsigned long);
List *_implicit_free_data freed_list(List *);
List *_implicit_free_data freed_gen_first(List*, void(*)(void*));
List *_implicit_free_data freed_gen_last(List *, void(*)(void*));
List *_implicit_free_data freed_gen_at(List *, unsigned long, void(*)(void*));
List *_implicit_free_data freed_gen_list(List *, void(*)(void*));
List *attach(List*, List*);
unsigned printl(List *, void (*)(const void *));
unsigned printl_b(List *, void (^)(const void *));
unsigned long printl_str(List*);
unsigned long printl_int(List*, unsigned char);
unsigned long printl_char(List*);
unsigned long printl_double(List*);
void permutl(List *, unsigned long, unsigned long);
List *split_chrstr(List *, char *, char);
List *split_strstr(List *, char *, char *);
List *split_chrstrex(List *, char *, char);
List *split_strstrex(List *, char *, char *);
List *_implicit_alloc_data splitcpy_chrstr(List *, char *, char);
List *_implicit_alloc_data splitcpy_strstr(List *, char *, char *);
List *_implicit_alloc_data splitcpy_chrstrex(List *, char *, char);
List *_implicit_alloc_data splitcpy_strstrex(List *, char *, char *);
void list_heapsort(List *, int (*)(const void*,const void*));
void list_heapsort_b(List *, int (^)(const void*,const void*));
int list_dsearch(List *, const void *, int (*)(const void *, const void *));
int list_dsearch_b(List *, const void *, int (^)(const void *, const void *));
void mix_list(List *L);
List *_implicit_alloc_data copy_list(List *, size_t);
List *insert(List *, void *, int (*)(const void*,const void*));
List *_implicit_alloc_data insertd(List *, void *, size_t, int (*)(const void*,const void*));
List *insertn(List *, int (*)(const void*,const void*), unsigned long, ...);
List *_implicit_alloc_data insertdn(List *, size_t, int (*)(const void*,const void*), unsigned long, ...);
void list_tofile_bin_static(List *, char *, size_t);
void list_tofile_with_method_bin_static(List *, char *, void (*)(const void *, FILE *));
List *_implicit_alloc_data new_list_fromfile_bin_static(char *, size_t);

#endif

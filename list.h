#ifndef __LIST__
#define __LIST__

struct List_t
{
	void *data;
	struct List_t *next;
};

typedef struct List_t List;
typedef struct List_t Cell;

unsigned long len_list(List*);
List *new_list(unsigned long, ...);
List *empty_list();
List *add_begin(List *, void*);
List *add_end(List *, void*);
List *add_at(List *, void*, unsigned long);
List *add_nbegin(List *, unsigned long, ...);
List *add_nend(List *, unsigned long, ...);
List *add_nat(List *, unsigned long, unsigned long, ...);
List *add_int(List *, long);
List *add_nint(List *, unsigned long, ...);
List *add_double(List *, double);
List *add_ndouble(List *, unsigned long, ...);
List *add_str(List *, char *);
List *add_nstr(List *, unsigned long, ...);
void set_first(List *, void *);
void setd_first(List *, void *);
void set_last(List *, void *);
void setd_last(List *, void *);
void set_at(List *L, unsigned long i, void *data);
void setd_at(List *, unsigned long, void *);
void *get_first(List *);
void *get_last(List *);
void *get_at(List *, unsigned long);
List *free_first(List *);
List *free_last(List *);
List *free_at(List *, unsigned long);
List *free_list(List*);
List *freed_first(List *);
List *freed_last(List *);
List *freed_at(List *, unsigned long);
List *freed_list(List *);
List *attach(List*, List*);
unsigned printl(List *, void (*)(const void *));
unsigned printl_b(List *, void (^)(const void *));
unsigned long printl_str(List*);
unsigned long printl_int(List*, unsigned char);
unsigned long printl_char(List*);
unsigned long printl_double(List*);
void permutl(List *, unsigned long, unsigned long);
List *split_chrstr(List *, char *, char);
List *splitd_chrstr(List *, char *, char);
List *split_strstr(List *, char *, char *);
List *splitd_strstr(List *, char *, char *);
List *split_chrstrex(List *, char *, char);
List *splitd_chrstrex(List *, char *, char);
List *split_strstrex(List *, char *, char *);
List *splitd_strstrex(List *, char *, char *);
void list_heapsort(List *, int (*)(const void*,const void*));
void list_heapsort_b(List *, int (^)(const void*,const void*));
int list_dsearch(List *, const void *, int (*)(const void *, const void *));
int list_dsearch_b(List *, const void *, int (^)(const void *, const void *));
void mix_list(List *L);



#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "list.h"


List *new_list(unsigned long n, ...)
{
	if(!n)
		return empty_list();
	List *L = empty_list();
	va_list ptr;
	va_start(ptr, n);
	for(int i = 0; i < n; i++)
	{
		L = add_end(L, va_arg(ptr, void*));
	}
	va_end(ptr);

	return L;
}

List *empty_list()
{
	return NULL;
}

unsigned long len_list(List* L)
{
	unsigned long i = 0;
	while(L)
	{
		i++;
		L = L->next;
	}
	return i;
}

static Cell *create_cell(void *);
static Cell *create_cell(void *data)
{
	Cell *cell = (Cell*)malloc(sizeof(Cell));
	if(!cell)
	{
		fprintf(stderr, "\033[91mallocation error\033[0m\n");
		return NULL;
	}
	cell->data = data;
	cell->next = NULL;

	return cell;
}

List * _implicit_alloc_data add_int(List *L, long val)
{
	L = add_end(L, malloc(8));
	*(long*)get_last(L) = (long)val;

	return L;
}

List * _implicit_alloc_data add_nint(List *L, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(long i = 0; i < n; i++)
	{
		long tmp = va_arg(ptr, long);
		L = add_int(L, tmp);
	}
	va_end(ptr);

	return L;
}

List * _implicit_alloc_data add_str(List *L, char *str)
{
	L = add_end(L, malloc(strlen(str)));
	strcpy(get_last(L), str);

	return L;
}

List * _implicit_alloc_data add_nstr(List *L, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(long i = 0; i < n; i++)
	{
		char *tmp = va_arg(ptr, char*);
		L = add_str(L, tmp);
	}
	va_end(ptr);

	return L;
}

List * _implicit_alloc_data add_double(List *L, double val)
{
	L = add_end(L, malloc(8));
	*(double*)get_last(L) = (double)val;

	return L;
}

List * _implicit_alloc_data add_ndouble(List *L, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(long i = 0; i < n; i++)
	{
		double tmp = va_arg(ptr, double);
		L = add_double(L, tmp);
	}
	va_end(ptr);

	return L;
}


List *add_begin(List *L, void *data)
{
	Cell *firstCell = create_cell(data);
	if(!firstCell)
	{
		return L;
	}
	firstCell->next = L;

	return firstCell;
}




List *add_end(List *L, void *data)
{
	if(!L)
		return add_begin(L, data);
	List *p = L;
	Cell *endCell = create_cell(data);
	if(!endCell)
	{
		return L;
	}
	while(p->next)
	{
		p = p->next;
	}
	p->next = endCell;

	return L;
}


List *add_at(List *L, void *data, unsigned long i)
{
	unsigned long j;
	List *cur = L;
	List *pshift;
	if(i == 0)
	{
		return add_begin(L, data);
	}
	if(i == len_list(L))
	{
		return add_end(L, data);
	}
	if(i > len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return L;
	}
	for(j = 1; j < i; j++)
	{
		cur = cur->next;
	}
	Cell *cell = create_cell(data);
	if(!cell)
	{
		return L;
	}
	pshift = cur->next;
	cell->next = pshift;
	cur->next = cell;

	return L;
}



List *add_nbegin(List *L, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(unsigned long i = 0; i < n; i++)
	{
		L = add_begin(L, va_arg(ptr, void*));
	}
	va_end(ptr);

	return L;
}

List *add_nend(List *L, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(unsigned long i = 0; i < n; i++)
	{
		L = add_end(L, va_arg(ptr, void*));
	}
	va_end(ptr);

	return L;
}

List *add_nat(List *L, unsigned long i, unsigned long n, ...)
{
	va_list ptr;
	va_start(ptr, n);
	for(unsigned long j = 0; j < n; j++)
	{
		L = add_at(L, va_arg(ptr, void*), j+i);
	}
	va_end(ptr);

	return L;
}

void set_first(List *L, void *data)
{
	L->data = data;
}

void _implicit_free_data setd_first(List *L, void *data)
{
	free(L->data);
	L->data = data;
}

void set_last(List *L, void *data)
{
	if(!L)
		return;
	while(L->next)
	{
		L = L->next;
	}
	L->data = data;
}

void _implicit_free_data setd_last(List *L, void *data)
{
	if(!L)
		return;
	while(L->next)
	{
		L = L->next;
	}
	free(L->data);
	L->data = data;
}


void set_at(List *L, unsigned long i, void *data)
{
	int j;
	if(i == 0)
	{
		set_first(L, data);
	}
	if(i == len_list(L)-1)
	{
		set_last(L, data);
	}
	if(i >= len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return;
	}
	for(j = 0; j < i; j++)
	{
		L = L->next;
	}

	L->data = data;
}

void _implicit_free_data setd_at(List *L, unsigned long i, void *data)
{
	int j;
	if(i == 0)
	{
		setd_first(L, data);
	}
	if(i == len_list(L)-1)
	{
		setd_last(L, data);
	}
	if(i >= len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return;
	}
	for(j = 0; j < i; j++)
	{
		L = L->next;
	}
	free(L->data);
	L->data = data;
}

void *get_first(List *L)
{
	if(!L)
		return NULL;
	return L->data;
}

void *get_last(List *L)
{
	if(!L)
		return NULL;
	while(L->next)
	{
		L = L->next;
	}
	return L->data;
}


void *get_at(List *L, unsigned long i)
{
	int j;
	if(i == 0)
	{
		return get_first(L);
	}
	if(i == len_list(L)-1)
	{
		return get_last(L);
	}
	if(i >= len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return L;
	}
	for(j = 0; j < i; j++)
	{
		L = L->next;
	}

	return L->data;
}


List *free_first(List* L)
{
	if(!L)
		return NULL;
	List *p = L->next;
	free(L);

	return p;
}

List *free_last(List *L)
{
	if(!L)
		return NULL;
	List *p = L;
	List *prec;
	while(p->next)
	{
		prec = p;
		p = p->next;
	}
	free(p);
	prec->next = NULL;

	return L;
}

List *free_at(List *L, unsigned long i)
{
	int j;
	List *prec, *next, *p=L;
	if(i == 0)
	{
		return free_first(L);
	}
	if(i == len_list(L)-1)
	{
		return free_last(L);
	}
	if(i >= len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return L;
	}
	for(j = 0; j < i; j++)
	{
		prec = p;
		p = p->next;
		next = p->next;
	}
	free(p);
	prec->next = next;

	return L;
}


List * _implicit_free_data freed_first(List* L)
{
	if(!L)
		return NULL;
	List *p = L->next;
	free(L->data);
	free(L);

	return p;
}

List * _implicit_free_data freed_last(List *L)
{
	if(!L)
		return NULL;
	List *p = L;
	List *prec;
	while(p->next)
	{
		prec = p;
		p = p->next;
	}
	free(p->data);
	free(p);
	prec->next = NULL;

	return L;
}

List * _implicit_free_data freed_at(List *L, unsigned long i)
{
	int j;
	List *prec, *next, *p=L;
	if(i == 0)
	{
		return freed_first(L);
	}
	if(i == len_list(L)-1)
	{
		return freed_last(L);
	}
	if(i >= len_list(L))
	{
		fprintf(stderr, "\033[91mlist index out of band error: %lu > %lu\033[0m\n", i, len_list(L)-1);
		return L;
	}
	for(j = 0; j < i; j++)
	{
		prec = p;
		p = p->next;
		next = p->next;
	}
	free(p->data);
	free(p);
	prec->next = next;

	return L;
}

List *free_list(List* L)
{
	if(!L)
	{
		return NULL;
	}
	while(L)
	{
		L = free_first(L);
	}
	return NULL;
}

List * _implicit_free_data freed_list(List* L)
{
	if(!L)
	{
		return NULL;
	}
	while(L)
	{
		free(L->data);
		L = free_first(L);
	}
	return NULL;
}



unsigned long printl_str(List* L)
{
	printf("\n");
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		printf("%s\n", get_at(L, i));
	}
	printf("\n");

	return size;
}

unsigned long printl_char(List* L)
{
	printf("\n");
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		printf("%c\n", *(char*)get_at(L, i));
	}
	printf("\n");

	return size;
}

unsigned long printl_double(List* L)
{
	printf("\n");
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		printf("%lf\n", *(double*)get_at(L, i));
	}
	printf("\n");

	return size;
}



unsigned long printl_int(List* L, unsigned char o)
{
	printf("\n");
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		switch(o)
		{
			case 1:
				printf("%hhd\n", *(char*)get_at(L, i));
				break;

			case 2:
				printf("%hd\n", *(short*)get_at(L, i));
				break;

			case 8:
				printf("%ld\n", *(long*)get_at(L, i));
				break;

			default:
				printf("%d\n", *(int*)get_at(L, i));
				break;
		}
	}
	printf("\n");

	return size;
}

unsigned printl(List *L, void (*print)(const void *))
{
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		print(get_at(L, i));
	}

	return size;
}

unsigned printl_b(List *L, void (^print)(const void *))
{
	unsigned long size = len_list(L);
	for(int i = 0; i < size; i++)
	{
		print(get_at(L, i));
	}

	return size;
}


List* attach(List* dest, List* src)
{
	while(dest->next)
	{
		dest = dest->next;
	}
	dest->next = src;

	return empty_list();
}


List *split_chrstr(List *L, char *str, char target)
{
	char *ptr = NULL;
	char *beg = str;
	unsigned long len = strlen(str);
	L = add_end(L, str);
	while((ptr = strchr(str, target)) && str-beg < len)
	{
		str[ptr-str] = 0;
		str = ptr+1;
		L = add_end(L, ptr+1);
	}

	return L;
}

List * _implicit_alloc_data splitd_chrstr(List *L, char *str, char target)
{
	char *ptr = NULL;
	char *beg = str;
	char *tmp = NULL;
	unsigned long len = strlen(str);
	while((ptr = strchr(str, target)))
	{
		tmp = malloc(sizeof(char)*(ptr-str)+1);
		strncpy(tmp, str, ptr-str+1);
		tmp[ptr-str]=0;
		str = ptr+1;
		L = add_str(L, tmp);
		free(tmp);
	}
	tmp = malloc(sizeof(char)*strlen(str)+1);
	strncpy(tmp, str, strlen(str)+1);
	L = add_str(L, tmp);
	free(tmp);

	return L;
}

List *split_strstr(List *L, char *str, char *target)
{
	char *ptr = NULL;
	char *beg = str, *tmp=0;
	int ok=1;
	unsigned long len = strlen(str);
	while(ok && str-beg < len)
	{
		tmp=0;
		for(int j = 0; j < strlen(target); j++)
		{
			ptr = strchr(str, *(target+j));
			if(tmp && tmp < ptr)
				ptr = tmp;
			tmp = ptr;
		}
		if(!ptr)
			break;
		str[ptr-str] = 0;
		str = ptr+1;
		L = add_end(L, ptr+1);
	}

	return L;
}

List * _implicit_alloc_data splitd_strstr(List *L, char *str, char *target)
{
	char *ptr = NULL;
	char *beg = str, *tmp=0, *tmp2=0;
	int ok=1;
	unsigned long len = strlen(str);
	while(ok && str-beg < len)
	{
		tmp=0;
		for(int j = 0; j < strlen(target); j++)
		{
			ptr = strchr(str, *(target+j));
			if(tmp && tmp < ptr)
				ptr = tmp;
			tmp = ptr;
		}
		if(!ptr)
			break;
		tmp2 = malloc(sizeof(char)*(ptr-str)+1);
		strncpy(tmp2, str, ptr-str+1);
		tmp2[ptr-str]=0;
		str = ptr+1;
		L = add_str(L, tmp2);
		free(tmp2);
	}
	tmp2 = malloc(sizeof(char)*strlen(str)+1);
	strncpy(tmp2, str, strlen(str)+1);
	L = add_str(L, tmp2);
	free(tmp2);

	return L;
}

List *split_chrstrex(List *L, char *str, char target)
{
	L = split_chrstr(L, str, target);
	int i, s, j, k, ok=0;
	s = len_list(L);
	char index[] = "\n\t \0";
	for(i = 0; i < s; i++)
	{
		ok=0;
		for(j = 0; j < strlen((char*)get_at(L, i)); j++)
		{
			
			if(*((char*)get_at(L, i)+j) != ' ' && *((char*)get_at(L, i)+j) != '\n' &&
			*((char*)get_at(L, i)+j) != '\t' && *((char*)get_at(L, i)+j) != '\0')
			{
				ok = 1;
				k=3;
				j = strlen((char*)get_at(L, i));
			}
		}
		if(!ok)
		{
			L = free_at(L, i--);
			s = len_list(L);
		}
	}

	return L;
}

List * _implicit_alloc_data splitd_chrstrex(List *L, char *str, char target)
{
	L = split_chrstr(L, str, target);
	int i, s, j, k, ok=0;
	s = len_list(L);
	char index[] = "\n\t \0";
	for(i = 0; i < s; i++)
	{
		ok=0;
		for(j = 0; j < strlen((char*)get_at(L, i)); j++)
		{
			
			if(*((char*)get_at(L, i)+j) != ' ' && *((char*)get_at(L, i)+j) != '\n' &&
			*((char*)get_at(L, i)+j) != '\t' && *((char*)get_at(L, i)+j) != '\0')
			{
				ok = 1;
				k=3;
				j = strlen((char*)get_at(L, i));
			}
		}
		if(!ok)
		{
			L = free_at(L, i--);
			s = len_list(L);
		}
	}

	return L;
}

List *split_strstrex(List *L, char *str, char *target)
{
	L = split_strstr(L, str, target);
	int i, s, j, k, ok=0;
	s = len_list(L);
	for(i = 0; i < s; i++)
	{
		ok=0;
		for(j = 0; j < strlen((char*)get_at(L, i)); j++)
		{
			if(*((char*)get_at(L, i)+j) != ' ' && *((char*)get_at(L, i)+j) != '\n' &&
			*((char*)get_at(L, i)+j) != '\t' && *((char*)get_at(L, i)+j) != '\0')
			{
				ok = 1;
				k=3;
				j = strlen((char*)get_at(L, i));
			}
		}
		if(!ok)
		{
			L = free_at(L, i--);
			s = len_list(L);
		}
	}

	return L;
}

List * _implicit_alloc_data splitd_strstrex(List *L, char *str, char *target)
{
	L = splitd_strstr(L, str, target);
	int i, s, j, k, ok=0;
	s = len_list(L);
	for(i = 0; i < s; i++)
	{
		ok=0;
		for(j = 0; j < strlen((char*)get_at(L, i)); j++)
		{
			if(*((char*)get_at(L, i)+j) != ' ' && *((char*)get_at(L, i)+j) != '\n' &&
			*((char*)get_at(L, i)+j) != '\t' && *((char*)get_at(L, i)+j) != '\0')
			{
				ok = 1;
				k=3;
				j = strlen((char*)get_at(L, i));
			}
		}
		if(!ok)
		{
			L = free_at(L, i--);
			s = len_list(L);
		}
	}

	return L;
}


void permutl(List *L, unsigned long i, unsigned long j)
{
	void *tmp = get_at(L, i);
	set_at(L, i, get_at(L, j));
	set_at(L, j, tmp);
}


static void patern(List *L, unsigned long ifather, unsigned long size, int (*gcompare)(const void*,const void*))
{
	unsigned long ison1 = ifather*2+1;
	unsigned long ison2 = ison1+1;
	
	while(ison1 < size)
	{
		if(ison2 < size && gcompare(get_at(L, ison2), get_at(L, ison1)) > 0)
		{
			ison1 = ison2;
		}

		if(gcompare(get_at(L, ison1), get_at(L, ifather)) > 0)
		{
			permutl(L, ison1, ifather);
			ifather = ison1;
			ison1 = ifather*2+1;
			ison2 = ison1+1;
		}
		else
		{
			ison1 = size;
		}
	}
}

void list_heapsort(List *L, int (*gcompare)(const void*,const void*))
{
	unsigned long size = len_list(L);
	int i;
	for(i=size/2-1; i >= 0; i--)
	{
		patern(L, i, size, gcompare);
	}
	permutl(L, 0, size-1);
	for(i=size-1; i > 0; i--)
	{
		size--;
		patern(L, 0, size, gcompare);
		permutl(L, 0, size-1);
	}
}


static void patern_b(List *L, unsigned long ifather, unsigned long size, int (^gcompare)(const void*,const void*))
{
	unsigned long ison1 = ifather*2+1;
	unsigned long ison2 = ison1+1;
	
	while(ison1 < size)
	{
		if(ison2 < size && gcompare(get_at(L, ison2), get_at(L, ison1)) > 0)
		{
			ison1 = ison2;
		}

		if(gcompare(get_at(L, ison1), get_at(L, ifather)) > 0)
		{
			permutl(L, ison1, ifather);
			ifather = ison1;
			ison1 = ifather*2+1;
			ison2 = ison1+1;
		}
		else
		{
			ison1 = size;
		}
	}
}

void list_heapsort_b(List *L, int (^gcompare)(const void*,const void*))
{
	unsigned long size = len_list(L);
	int i;
	for(i=size/2-1; i >= 0; i--)
	{
		patern_b(L, i, size, gcompare);
	}
	permutl(L, 0, size-1);
	for(i=size-1; i > 0; i--)
	{
		size--;
		patern_b(L, 0, size, gcompare);
		permutl(L, 0, size-1);
	}
}


int list_dsearch(List *L, const void *target, int (*gcompare)(const void *, const void *))
{
	long ibegin=0;
	long iend=len_list(L)-1;
	long imiddle;
	long compResult;
	while(ibegin <= iend)
	{
		imiddle = (iend+ibegin)/2;
		compResult = gcompare(get_at(L, imiddle), target);
		if(compResult < 0)
		{
			ibegin = imiddle+1;
		}
		else
		{
			if(compResult > 0)
				iend = imiddle-1;
			else
				return imiddle;
		}
	}

	return -1;
}


int list_dsearch_b(List *L, const void *target, int (^gcompare)(const void *, const void *))
{
	long ibegin=0;
	long iend=len_list(L)-1;
	long imiddle;
	long compResult;
	while(ibegin <= iend)
	{
		imiddle = (iend+ibegin)/2;
		compResult = gcompare(get_at(L, imiddle), target);
		if(compResult < 0)
		{
			ibegin = imiddle+1;
		}
		else
		{
			if(compResult > 0)
				iend = imiddle-1;
			else
				return imiddle;
		}
	}

	return -1;
}


void mix_list(List *L)
{
	int i;
	unsigned long len = len_list(L);
	for(i = 0; i < len; i++)
	{
		permutl(L, rand()%len, rand()%len);
	}
}









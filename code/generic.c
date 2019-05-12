#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>
#include "generic.h"



static void gpatern(void *, const unsigned long, const size_t, unsigned long,int(*)(const void*,const void*), char*);
static void _heap_gswap(void *, void *, const size_t, char *);

void gswap(void *p1, void *p2, const size_t nbytes)
{
	char *tmp = malloc(sizeof(char)*nbytes);
	if(!tmp)
	{
		perror("\033[96mvoid gswap(void *p1, void *p2, const size_t nbytes)\033[0m ");
		return;
	}
	unsigned i;
	for(i = 0; i < nbytes; i++)
	{
		tmp[i] = *(char*)(p1+i);
		*(char*)(p1+i) = *(char*)(p2+i);
		*(char*)(p2+i) = tmp[i];
	}
	free(tmp);
}

static void _heap_gswap(void *p1, void *p2, const size_t nbytes, char *tmp)
{
	unsigned i;
	for(i = 0; i < nbytes; i++)
	{
		tmp[i] = *(char*)(p1+i);
		*(char*)(p1+i) = *(char*)(p2+i);
		*(char*)(p2+i) = tmp[i];
	}
}

static void gpatern(void *ptr, const unsigned long nelem, const size_t mpe, unsigned long ifather,int __no_nul_return (*gcompare)(const void*,const void*), char*tmp)
{
	unsigned long ison1 = ifather*2+1;
	unsigned long ison2 = ison1+1;
	while(ison1 < nelem)
	{
		if(ison2 < nelem && gcompare(ptr+(ison2*mpe), ptr+(ison1*mpe)) > 0)
		{
			ison1 = ison2;
		}
		if(gcompare(ptr+(ison1*mpe), ptr+(ifather*mpe)) > 0)
		{
			_heap_gswap(ptr+(ison1*mpe), ptr+(ifather*mpe), mpe, tmp);
			ifather = ison1;
			ison1 = ifather*2+1;
			ison2 = ison1+1;
		}
		else
		{
			ison1 = nelem;
		}
	}
}

void gheapsort(void *ptr, unsigned long nelem, const size_t mpe, int __no_nul_return (*gcompare)(const void*, const void*))
{
	char *tmp = malloc(sizeof(char)*mpe);
	int i;
	for(i = nelem/2-1; i >= 0; i--)
	{
		gpatern(ptr, nelem, mpe, i, gcompare, tmp);
	}
	_heap_gswap(ptr, ptr+(nelem-1)*mpe, mpe, tmp);
	for(i = nelem-1; i > 0; i--)
	{
		nelem--;
		gpatern(ptr, nelem, mpe, 0, gcompare, tmp);
		_heap_gswap(ptr, ptr+(nelem-1)*mpe, mpe, tmp);
	}
	free(tmp);
}


int gseqsearch(const void *vec, const void *target, const int nbel, const size_t nbytes, int __nul_return (*gcompare)(const void *, const void *))
{
	int i;
	for(i = 0; i < nbel && gcompare(vec+i*nbytes, target); i++);

	return i<nbel?i:-1;
}

int gdsearch(const void *vec, const void *target, const int nbel, const size_t nbytes, int __nul_return (*gcompare)(const void *, const void *))
{
	int ibegin=0;
	int iend=nbel-1;
	int imiddle;
	int compResult;
	while(ibegin <= iend)
	{
		imiddle = (iend+ibegin)/2;
		compResult = gcompare(vec+imiddle*nbytes, target);
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

static void gpatern_b(void *ptr, const unsigned long nelem, const size_t mpe, unsigned long ifather,int __no_nul_return (^gcompare)(const void*,const void*), char*tmp)
{
	unsigned long ison1 = ifather*2+1;
	unsigned long ison2 = ison1+1;
	
	while(ison1 < nelem)
	{
		if(ison2 < nelem && gcompare(ptr+(ison2*mpe), ptr+(ison1*mpe)) > 0)
		{
			ison1 = ison2;
		}

		if(gcompare(ptr+(ison1*mpe), ptr+(ifather*mpe)) > 0)
		{
			_heap_gswap(ptr+(ison1*mpe), ptr+(ifather*mpe), mpe, tmp);
			ifather = ison1;
			ison1 = ifather*2+1;
			ison2 = ison1+1;
		}
		else
		{
			ison1 = nelem;
		}
	}
}

void gheapsort_b(void *ptr, unsigned long nelem, const size_t mpe, int __no_nul_return (^gcompare)(const void*, const void*))
{
	char *tmp = malloc(sizeof(char)*mpe);
	int i;
	for(i = nelem/2-1; i >= 0; i--)
	{
		gpatern_b(ptr, nelem, mpe, i, gcompare, tmp);
	}
	_heap_gswap(ptr, ptr+(nelem-1)*mpe, mpe, tmp);
	for(i = nelem-1; i > 0; i--)
	{
		nelem--;
		gpatern_b(ptr, nelem, mpe, 0, gcompare, tmp);
		_heap_gswap(ptr, ptr+(nelem-1)*mpe, mpe, tmp);
	}
	free(tmp);
}


int gseqsearch_b(const void *vec, const void *target, const int nbel, const size_t nbytes, int __nul_return (^gcompare)(const void *, const void *))
{
	int i;
	for(i = 0; i < nbel && gcompare(vec+i*nbytes, target); i++);

	return i<nbel?i:-1;
}

int gdsearch_b(const void *vec, const void *target, const int nbel, const size_t nbytes, int __nul_return (^gcompare)(const void *, const void *))
{
	int ibegin=0;
	int iend=nbel-1;
	int imiddle;
	int compResult;
	while(ibegin <= iend)
	{
		imiddle = (iend+ibegin)/2;
		compResult = gcompare(vec+imiddle*nbytes, target);
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


void __gprint(void *data, char *typeName)
{
	if(!strcmp(typeName, "char")) printf("%hhd\n", *(char*)data);
	 else if(!strcmp(typeName, "unsigned char")) printf("%hhu\n", *(unsigned char*)data);
	 else if(!strcmp(typeName, "short")) printf("%hd\n", *(short*)data);
	 else if(!strcmp(typeName, "unsigned short")) printf("%hu\n", *(unsigned short*)data);
	 else if(!strcmp(typeName, "int")) printf("%d\n", *(int*)data);
	 else if(!strcmp(typeName, "unsigned")) printf("%u\n", *(unsigned*)data);
	 else if(!strcmp(typeName, "long")) printf("%ld\n", *(long*)data);
	 else if(!strcmp(typeName, "unsigned long")) printf("%lu\n", *(unsigned long*)data);
	 else if(!strcmp(typeName, "float")) printf("%f\n", *(float*)data);
	 else if(!strcmp(typeName, "double")) printf("%lf\n", *(double*)data);
	 else if(!strcmp(typeName, "char *")) printf("%s\n", (char*)data);
	 else printf("%p\n", *(char**)data);
}



















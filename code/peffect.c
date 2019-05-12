#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "peffect.h"


void print_delay(const char *msg, Millsec delay)
{
	char *pmsg = (char*)msg;
	while(*pmsg)
	{
		fprintf(stderr, "%c", *pmsg);
		usleep(delay*1000);
		pmsg++;
	}
}

void print_delay_max(const char *msg, Millsec delay)
{
	char *pmsg = (char*)msg;
	delay /= strlen(msg);
	while(*pmsg)
	{
		fprintf(stderr, "%c", *pmsg);
		usleep(delay*1000);
		pmsg++;
	}
}


void print_bin(const size_t nbytes, const void* data)
{
	int i, j;
	for(i = nbytes-1; i >= 0; i--)
	{
		for(j = 0; j < 8; j++)
			printf("%d", ((*(char*)(data+i)) >> (8-j-1)) & 1);
		printf(" ");
	}
	printf("\n");
}

void print_bini(const size_t nbits, const int data)
{
	unsigned i;
	for(i = 0; i < nbits; i++)
	{
		printf("%d", (data>>(nbits-i-1))&1);
	}
	printf("\n");
}

void print_binf(const float data)
{
	int i;
	int *dt = (int*)&data;
	for(i = 0; i < 32; i++)
	{
		printf("%d", (*dt>>(32-i-1))&1);
	}
	printf("\n");
}

void print_bind(const double data)
{
	int i;
	long *dt = (long*)&data;
	for(i = 0; i < 64; i++)
	{
		printf("%ld", (*dt>>(64-i-1))&1);
	}
	printf("\n");
}

static void print_limit_box(const int);
static void print_str_middle_box(const char *);

static void print_limit_box(const int limit)
{
	printf("+--");
	for(int i=0;i<limit;i++) printf("-");
	printf("--+");
}


static void print_str_middle_box(const char *msg)
{
	printf("|  %s  |", msg);
}


void print_box(const char *msg)
{
	print_limit_box(strlen(msg));
	printf("\n");
	print_str_middle_box(msg);
	printf("\n");
	print_limit_box(strlen(msg));
	printf("\n");
}







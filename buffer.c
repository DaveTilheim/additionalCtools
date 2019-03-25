#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strplus.h"
#include "buffer.h"


void clear_buffer(void)
{
	int c = getchar();
	while(c != '\n' && c != EOF)
	{
		c = getchar();
	}
}


unsigned get_secure_int(void)
{
	char buffer[128];
	do
	{
		printf("> ");
		scanf("%127s", buffer);
	}while(!isdigit_str(buffer) && printf("Ce n'est pas un nombre\n"));

	return atoi(buffer);
}

int get_secure_signed_int(void)
{
	char buffer[128];
	bool signedNum = false;
	do
	{
		printf("> ");
		fflush(stdin);
		scanf("%127s", buffer);
		if(buffer[0] == '-')
		{
			signedNum = true;
			buffer[0] = '0';
		}
	}while(!isdigit_str(buffer) && printf("Ce n'est pas un nombre\n"));

	return signedNum?-atoi(buffer):atoi(buffer);
}

float get_secure_float(void)
{
	char buffer[128];
	bool signedNum = false;
	int coma=-1, i;
	do
	{
		printf("> ");
		fflush(stdin);
		scanf("%127s", buffer);
		if(buffer[0] == '-')
		{
			signedNum = true;
			buffer[0] = '0';
		}
		for(i=0; i < strlen(buffer); i++)
			if(buffer[i] == '.')
			{
				coma=i;
				buffer[i] = '0';
				i=strlen(buffer);
			}
	}while(!isdigit_str(buffer) && printf("Ce n'est pas un nombre\n"));
	if(coma != -1)
		buffer[coma] = '.';
	return signedNum?-atof(buffer):atof(buffer);
}

void wait_return(void)
{
	printf("> ");
	clear_buffer();
	getchar();
}

void wait_return_noflush(void)
{
	printf("> ");
	getchar();
}


void print_and_encode(const char *msg, const char *format, void *adress)
{
	printf("%s", msg);
	scanf(format, adress);
	clear_buffer();
}

static void del_return_char(char *);
static void del_return_char(char *str)
{
	while(*str)
	{
		if(*str == '\n')
			*str = 0;
		str++;
	}
}

void print_and_encode_with_space(const char *msg, char *adress, const size_t maxCar)
{
	char buffer[151];
	do
	{
		printf("%s", msg);
		fgets(buffer, maxCar, stdin);
		del_return_char(buffer);
	}while((strlen(buffer) == 0 || strlen(buffer) >= maxCar) && printf("Vous n'avez rien entré"));
	buffer[maxCar] = 0;
	strcpy(adress, buffer);
}

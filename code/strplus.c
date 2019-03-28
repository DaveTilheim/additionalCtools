#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strplus.h"


bool imprimable(char *str)
{
	while(*str)
	{
		if(!isprint(*str))
		{
			printf("Ce caractère ne convient pas...");
			return false;
		}
		str++;
	}

	return true;
}

bool isalpha_str(char *str)
{
	while(*str)
	{
		if(!isalpha(*str))
		{
			return false;
		}
		str++;
	}

	return true;
}

bool isdigit_str(char *str)
{
	while(*str)
	{
		if(!isdigit(*str))
		{
			return false;
		}
		str++;
	}

	return true;
}

void toupper_str(char *str)
{
	while(*str)
	{
		*str = toupper(*str);
		str++;
	}
}

void tolower_str(char *str)
{
	while(*str)
	{
		*str = tolower(*str);
		str++;
	}
}

void initiale_upper(char *str)
{
	bool spaceFLG = true;
	while(*str)
	{
		if(spaceFLG)
		{
			spaceFLG = false;
			*str = toupper(*str);
		}
		if(*str == ' ')
			spaceFLG = true;
		str++;
	}
}

void replace_str(char *str, char *target, char *newStr)
{
	char *ptrRemp = NULL;
	unsigned long targetLen = strlen(target);
	unsigned long newStrLen = strlen(newStr);
	unsigned long strLen = strlen(str);
	int i;
	while((ptrRemp = strstr(str, target)))
	{
		if(targetLen == newStrLen)
		{
			stpncpy(ptrRemp, newStr, newStrLen);
		}
		else
		{
			if(targetLen < newStrLen)
			{
				for(i = strLen-1+(newStrLen-targetLen); i >= (int)(ptrRemp-str+(newStrLen-targetLen)); i--)
				{
					str[i] = str[i-(newStrLen-targetLen)];
				}
				stpncpy(ptrRemp, newStr, newStrLen);
				strLen = strlen(str);
			}
			else
			{
				stpncpy(ptrRemp, newStr, newStrLen);
				for(i = ptrRemp-str+newStrLen; i < (int)strLen; i++)
				{
					str[i] = str[i+(targetLen-newStrLen)];
				}
				str[strLen-1] = 0;
				strLen--;
			}
		}
	}
}

void replace_chr(char *str, char target, char newChr)
{
	char *ptrRemp = NULL;
	while((ptrRemp = strchr(str, target)))
	{
		str[ptrRemp-str] = newChr;
	}
}

void strip_str(char *str, char *stripelement)
{
	replace_str(str, stripelement, "");
}

void stripctrl_str(char *str)
{
	replace_str(str, "\n", "");
	replace_str(str, "\t", "");
	replace_str(str, "\r", "");
	replace_str(str, "\v", "");
	replace_str(str, "\b", "");
}

void binstr(char *dest, size_t nbytes, void *data)
{
	int i, j, k=0;
	for(i = nbytes-1; i >= 0; i--)
	{
		for(j = 0; j < 8; j++)
			dest[k++] = '0'+(((*(char*)(data+i)) >> (8-j-1)) & 1);
	}
}





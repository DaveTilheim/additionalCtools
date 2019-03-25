#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strplus.h"
#include "fileplus.h"

bool file_exists(const char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if(!fp)
		return false;
	else
	{
		fclose(fp);
		return true;
	}
}

int create_file(const char *fileName)
{
	if(file_exists(fileName))
		return -1;
	FILE *fp = fopen(fileName, "w");
	if(!fp)
		return -2;
	fclose(fp);

	return 0;
}


void ls_str(char *lsstorage)
{
	system("ls > ._ls_string_temp_");
	long len=0;
	char buffer[1024];
	FILE *fp = fopen("._ls_string_temp_", "rt");
	if(!fp)
		return;
	
	while(fscanf(fp, "%s", buffer)==1)
	{
		strcat(buffer, " ");
		len = strlen(buffer);
		strcpy(lsstorage, buffer);
		lsstorage+=len;
	}
	fclose(fp);
	remove("._ls_string_temp_");
}


void cat_str(char *catstorage, const char *filename)
{
	char buffer[2];
	long len = 0;
	FILE *fp = fopen(filename, "rt");
	if(!fp)
		return;
	
	while(fscanf(fp, "%c", buffer)==1)
	{
		len = strlen(buffer);
		strcpy(catstorage, buffer);
		catstorage+=len;
	}
	fclose(fp);
}

void dcat_str(char **catstorage, const char *filename)
{
	char buffer[2], *temp=NULL;
	long len = 0;
	FILE *fp = fopen(filename, "rt");
	if(!fp)
		return;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	*catstorage = malloc(sizeof(char)*len+1);
	temp = *catstorage;
	if(!*catstorage)
	{
		fclose(fp);
		return;
	}
	while(fscanf(fp, "%c", buffer)==1)
	{
		len = strlen(buffer);
		strcpy(temp, buffer);
		temp+=len;
	}
	fclose(fp);
}

long get_fsize(const char *filename)
{
	long size=0;
	FILE *fp = fopen(filename, "rt");
	if(!fp)
		return -1;
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);

	return size;
}


void cat_file(const char *dest, const char *src)
{
	if(!file_exists(dest) || !file_exists(src))
		return;
	char buffer[128] = "cat ";
	strcat(buffer, src);
	strcat(buffer, " >> ");
	strcat(buffer, dest);
	system(buffer);
}








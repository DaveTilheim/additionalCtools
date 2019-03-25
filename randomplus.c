#include <stdlib.h>
#include <stdio.h>
#include "randomplus.h"

int getrand(const int lim1, const int lim2)
{
	return lim1<lim2?rand()%(lim2-lim1+1)+lim1:rand()%(lim1-lim2+1)+lim2;
}

void fillrand(int *ptr, const int size, const int lim1, const int lim2)
{
	int i;
	for(i = 0; i < size; i++)
	{
		*(ptr+i) = getrand(lim1, lim2);
	}
}

double fgetrand(const int lim1, const int lim2)
{
	double randvalue = (double)getrand(lim1, lim2-1);
	randvalue += getrand(0, 1000000)/1000000.0;
	return randvalue;
}

void ffillrand(double *ptr, const int size, const int lim1, const int lim2)
{
	int i;
	for(i = 0; i < size; i++)
	{
		*(ptr+i) = fgetrand(lim1, lim2);
	}
}

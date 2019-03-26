#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

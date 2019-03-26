#ifndef __STRPLUS__
#define __STRPLUS__

typedef enum
{
	false, true
}bool;

bool imprimable(char *);
void toupper_str(char *);
void tolower_str(char *);
bool isalpha_str(char *);
bool isdigit_str(char *);
void initiale_upper(char *);
void replace_str(char *, char *, char *);
void replace_chr(char *, char, char);
void strip_str(char *, char *);
void stripctrl_str(char *);
#define bins(dest, value) binstr(dest, sizeof(value), &value)
void binstr(char *, size_t, void *);

#endif

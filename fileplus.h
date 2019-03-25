#ifndef __FILEPLUS__
#define __FILEPLUS__

bool file_exists(const char *);
int create_file(const char *);
void ls_str(char *);
void cat_str(char *, const char *);
void dcat_str(char **, const char *);
long get_fsize(const char *);
void cat_file(const char *, const char *);

#endif

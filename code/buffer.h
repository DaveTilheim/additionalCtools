#ifndef __BUFFER__
#define __BUFFER__

#define debug(str) fprintf(stderr, "%s", str)

void clear_buffer(void);
unsigned get_secure_int(void);
int get_secure_signed_int(void);
float get_secure_float(void);
void print_and_encode(const char *, const char *, void *);
void print_and_encode_with_space(const char *, char *, const size_t);
void wait_return(void);
void wait_return_noflush(void);

#endif

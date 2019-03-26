#ifndef __RANDOMPLUS__
#define __RANDOMPLUS__
#define resetseed() srand(time(NULL))

int getrand(const int, const int);
void fillrand(int *, const int, const int, const int);
double fgetrand(const int, const int);
void ffillrand(double *, const int, const int, const int);

#endif

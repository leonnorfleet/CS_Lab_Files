#ifndef RAND64_SW_H
#define RAND64_SW_H

#include <stdio.h>

extern FILE* urandstream;
extern long seed;
extern struct drand48_data buffer;

void software_rand64_init (char *filename);

unsigned long long
software_rand64 (void);

void software_rand64_fini (void);

#endif // RAND64_SW_H

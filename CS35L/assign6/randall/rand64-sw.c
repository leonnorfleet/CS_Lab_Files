#include "rand64-sw.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* urandstream;
long seed;
struct drand48_data buffer;

void
software_rand64_init (char *filename)
{
  if (filename == NULL)
    {
      seed = (long)time(NULL);
      srand48_r(seed, &buffer);
	    
      return;
    }
  
  urandstream = fopen (filename, "r");
  if (! urandstream)
    {
      fprintf(stderr, "%s: file not found\n", "randall");
      exit(1);
    }
}

unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (urandstream == NULL) // No file
    {
      //srand48_r(seed, &buffer);
      long int temp1, temp2;
      lrand48_r(&buffer, &temp1);
      lrand48_r(&buffer, &temp2);
      
      x = ((unsigned long long int)temp1 << 32 |
           (unsigned long long int)(temp2));
      //printf("%llu\n", x);
    }
  else // File given
    {
      if (fread (&x, sizeof x, 1, urandstream) != 1)
	{
	  fprintf(stderr, "%s: %s: error with long int generation\n", "randall", "rand64-sw");
	  exit(1);
	}
    }
  return x;
}

void
software_rand64_fini (void)
{
  if (urandstream == NULL)
    return;
  fclose (urandstream);
}

/*
int main(int argc, char **argv)
{
  unsigned long long res;
  if (argc > 1)
    {
      software_rand64_init(argv[1]);
      res = software_rand64();
      software_rand64_fini();
    }
  else
      res = software_rand64();
  
  printf("REMOVE MAIN AND ADD TO RANDALL\nOutput: %llu\n", res);
  
  return 0;
}
*/

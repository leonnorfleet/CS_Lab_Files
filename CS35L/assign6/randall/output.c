#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int
writebytes (unsigned long long x, int outbytes)
{
  do
    {
      if (putchar(x) < 0)
	return 0;
      x >>= CHAR_BIT;
      outbytes--;
    }
  while (0 < outbytes);

  return 1;
}

void output_bytes(unsigned long long (*rand64) (void), long long nbytes, char* option)
{
  if (*option == 's')
    {
      int wordsize = sizeof rand64();
      do
	{
	  unsigned long long x = rand64();
	  int outbytes = nbytes < wordsize ? nbytes : wordsize;
	  if (!writebytes (x, outbytes))
	    {
	      exit(1);
	    }
	  nbytes -= outbytes;
	}
      while(0 < nbytes);
    }
  else
    {
      int blocksize = atoi(option);
      do
	{
	  unsigned long long x = rand64();
	  unsigned char *buffer = malloc(blocksize);

	  if (buffer == NULL)
	    {
	      fprintf(stderr, "%s: output: memory allocation error\n", "randall");
	      exit(1);
	    }

	  for (int i = 0; i < blocksize; ++i)
	    {
	      buffer[i] = x & UCHAR_MAX;
	      x >>= CHAR_BIT;
	    }
	  
	  size_t wrotebytes = write(STDOUT_FILENO, buffer, nbytes < blocksize ? nbytes :
				    blocksize);

	  nbytes -= wrotebytes;

	  //printf("message: %d\n", wrotebytes);
				    
	  free(buffer);
	}
      while(0 < nbytes);
    }
  return;
}

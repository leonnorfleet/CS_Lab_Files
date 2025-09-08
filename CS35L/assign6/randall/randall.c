/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <cpuid.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "options.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "output.h"


/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  // Check arguments
  // Arguments Processing From options.c
  
  char* ivalue = (char*)malloc((7 * sizeof(char)) + 1);
  if (ivalue == NULL)
    {
      fprintf(stderr, "%s: memory allocation failed\n", "randall");
      exit(1);
    }
  char* ovalue = (char*)malloc((5 * sizeof(char)) + 1);
  if (ovalue == NULL)
    {
      fprintf(stderr, "%s: memory allocation failed\n", "randall");
      free(ivalue);
      exit(1);
    }
  
  strcpy(ivalue, "rdrand");
  strcpy(ovalue, "stdio");
  
  long long nbytes = process_opt(argc, argv, &ivalue, &ovalue);

  if (nbytes == 0)
    {
      free(ivalue);
      free(ovalue);
      return 0;
    }

  void (*initialize) ();
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  if (*ivalue == 'r')
    {
      if (!rdrand_supported())
	{
	  fprintf(stderr, "%s: rdrand not available\n", "randall");
	  exit(1);
	}
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;

      initialize();
    }
  else {
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;

    switch(*ivalue)
      {
      case 'l':
	initialize(NULL);
	break;

      case '/':
	initialize(ivalue);
	break;

      default:
	exit(1);
      }
  }

  //printf("%lld, %s, %s, %llu\n", nbytes, ivalue, ovalue, x);

  output_bytes(rand64, nbytes, ovalue);
  
  finalize();
  free(ovalue);
  free(ivalue);
  
  return 0;
}

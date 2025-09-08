#include "options.h"
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

long long process_opt(int argc, char** argv, char** ivalue, char** ovalue) {

  int c;
  
  while ((c = getopt (argc, argv, "i:o:")) != -1)
    {
      switch(c)
	{
	case 'i':
	  if (!strcmp(optarg, "lrand48_r") || *optarg == '/')
	    {
	      char* temp = realloc(*ivalue, (strlen(optarg) + 1)  * sizeof(char));
	      if (temp == NULL)
		{
		  fprintf(stderr, "%s: memory allocation failed\n", "randall");
		  free(*ivalue);
		  free(*ovalue);
		  exit(1);
		}
	      *ivalue = temp;
	      strcpy(*ivalue, optarg);
	    }
	  else if (strcmp(optarg, "rdrand")) // bad option
	    {
	      fprintf (stderr, "%s: invalid argument: -%c %s\n", "randall", c, optarg);
	      free(*ivalue);
	      free(*ovalue);
	      exit(1);
	    }
	  break;
	  
	case 'o':
	  if ((is_digit(optarg) && atoi(optarg) > 0) || !strcmp(optarg, "stdio"))
	    {
	      char* temp = realloc(*ovalue, (strlen(optarg) + 1) * sizeof(char));
	      if (temp == NULL)
                {
                  fprintf(stderr, "%s: memory allocation failed\n", "randall");
                  free(*ivalue);
		  free(*ovalue);
                  exit(1);
                }
	      *ovalue = temp;
	      strcpy(*ovalue, optarg);
	    }
	  else
	    {
	      fprintf (stderr, "%s: invalid argument: -%c %s\n", "randall", c, optarg);
              free(*ivalue);
              free(*ovalue);
              exit(1);
	    }
	  break;

	case '?': // error handling
	case ':': // error handling
	  free(*ivalue);
	  free(*ovalue);
	  exit(1);
	  break;
	}
    }

  if (argv[optind] == NULL || !is_digit(argv[optind])) // no NBYTES
    {
      fprintf(stderr, "%s: usage: %s [OPTIONS] NBYTES\n", "randall", "./randall");
      free(*ivalue);
      free(*ovalue);
      exit(1);
    }

  if (optind != argc - 1) // too many args
    {
      fprintf(stderr, "%s: too many arguments given: ", "./randall");
      for (int i = optind + 1; argv[i] != NULL; ++i)
	{
	  printf("%s ", argv[i]);
	}
      printf("\n");
      free(*ivalue);
      free(*ovalue);
      exit(1);
    }

  long long nbytes;

  nbytes = strtoll(argv[optind], NULL, 10);
  
  if (nbytes == 0)
    {
      if (errno == EINVAL)
	{
	  free(*ivalue);
	  free(*ovalue);
	  fprintf(stderr, "%s: Conversion error occurred: %d\n", "randall", errno);
	  exit(1);
	}
    }

  if (nbytes == LLONG_MIN || nbytes == LLONG_MAX)
    {
      if (errno == ERANGE)
	{
	  free(*ivalue);
	  free(*ovalue);
	  fprintf(stderr, "%s: The value provided was out of range: %s\n", "randall", argv[optind]);
	  exit(1);
	}
    }
  
  return nbytes;
}

int is_digit(char* str) {
  for (char* ptr = str; *ptr != '\0'; ++ptr) {
    if (!isdigit(*ptr))
      return 0;
  }
  return 1;
}

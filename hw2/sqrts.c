

/* print square roots in C language.  R. Brown, 9/2010 */

#include <stdio.h>
#include <math.h>

main()
{
  int n;
  printf("n\tsqrt(n)\n----------------\n");
  for (n=0;  n<=5;  n++)
    printf("%d\t%f\n", n, sqrt(n));
  return 0;
}


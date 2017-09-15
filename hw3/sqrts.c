/* print square roots in C language.  R. Brown, 9/2010 */

#include <stdio.h>
#include <math.h>

int main()
{
  int n=0;
  printf("n\tsqrt(n)\n----------------\n");
  while (n<=5){
    printf("%d\t%f\n", n, sqrt(n)); 
    n++;
}
  return 0;
}
/*all square roots are printed*/

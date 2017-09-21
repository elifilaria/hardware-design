

/* print square roots in C language.  R. Brown, 9/2010 */

#include <stdio.h>
#include <math.h>

int n;

long factorial (int x){
  long ans=1;
  for (int i=1; i<=x; ++i)
    ans=ans*i;
  return ans;
}

int main()
{
  printf("n\tn!\n----------------\n");
  for (n=0;  n<=5;  n++)
    printf("%d\t%d\n", n, factorial(n));
  return 0;
}


/* print square roots in C language.  R. Brown, 9/2010 */

#include <stdio.h>
#include <math.h>

long factorial(int n){
  long ans = 1;
  for (int i=1; i<=n; i++)
    ans = ans*i;
  return ans;
}

int main()
{
  int n;
  printf("n\tn!\n----------------\n");
  for (n=0;  n<=5;  n++)
    printf("%d\t%f\n", n, factorial(n));
  return 0;
}


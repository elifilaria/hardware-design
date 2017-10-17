#include <stdio.h>
#include <math.h>

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return
	n*factorial(n-1);
}

main()
{
  int n = factorial(10);
  printf("%d\n", n);
  if (n == 3628800)
  	printf("Indeed, 10! is 3628800\n");
  return 0;
}


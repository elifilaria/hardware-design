#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	int max = atoi (argv[1]);
	int n;
  	printf("sqrt(n)\n--------\n");
  	for (n=0;  n<=max;  n++)
    	printf("%f\n", sqrt(n));
  	return 0;
}


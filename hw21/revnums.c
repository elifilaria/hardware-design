#include <stdio.h>
#include <stdlib.h>


int main() 
{
	unsigned int x;
	printf("%s", "Enter a non-negative integer: ");
	scanf("%d", &x);

	float *vals;
	vals = (float*) malloc(sizeof(float));

	printf("%s%d%s\n", "Enter ", x, " floating point value(s): ");
	int i;
	for (i = 0; i < x; i++)
	{
		scanf("%f", &vals[i]);
	}

	printf("%s\n", "In reverse order your input is: ");
	for (i = x-1; i >= 0 ; i--)
	{
 		printf("%g\n", vals[i]);
	}

	return 0;

}
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int main(int argc, char **argv)
{
	int max = atoi (argv[1]);
  	cout << "sqrt(n)" << endl << "--------" << endl;
  	for (int n=0;  n<=max;  n++)
    	cout << sqrt(n) << endl;
 	 return 0;
}


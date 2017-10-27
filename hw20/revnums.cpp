#include <iostream>
using namespace std;


int main() 
{
	unsigned int x;
	cout << "Enter a non-negative integer: ";
	cin >> x;

	float *vals;
	vals = new float [x];

	cout << "Enter " << x << " floating point value(s): " << endl;
	for (int i = 0; i < x; i++)
	{
		cin >> vals[i];
	}

	cout << "In reverse order your input is: " << endl;
	for (int i = x-1; i >= 0 ; i--)
	{
 		cout << vals[i] << endl;
	}

	return 0;

}
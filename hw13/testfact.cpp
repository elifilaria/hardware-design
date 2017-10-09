/* Example of recursion in C++ -- RAB 10/10 */

#include <iostream>
using namespace std;

int factorial(int n) {
  if (n == 0) 
    return 1;
  else
    return n * factorial(n-1);
}

int main() {
  int fact = factorial(10);
  cout << fact << endl;
  if (fact == 3628800)
  	cout << "Indeed, 10! = 3628800" << endl;
}

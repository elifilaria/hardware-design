/* example of iteration in C language.  RAB 9/10 */
#include <iostream>
#include <math.h>
using namespace std;

int main() {
  int n;
  int result = 0;  
  int i;
  
  cout << "Enter a positive integer: ";
  cin>> n;

  i = 0;
  do
    {
      result = result + i*i;
      i++;
    }
  while (i <= n);

  cout << "The sum of the first " << n << " squares is " << result << "\n";
  return 0;  
}

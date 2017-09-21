/* print factorials in C++ language.  R. Brown, 9/2010 */

#include <iostream>
#include <cmath>

using namespace std;

int n;
long factorial(int n){
  long ans = 1;
  int i=1;
  while (i<=n){
     ans = ans*i;
     i++;
  }
  return ans;
 }
int main()
{
  cout << "n\tn!" << endl << "----------------" << endl;
  n=0;
  while (n<=5){
    cout << n << "\t" << factorial(n) << endl;
    n++;
  }
  return 0;
}


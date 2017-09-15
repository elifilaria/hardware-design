/* print factorials in C++ language.  R. Brown, 9/2010 */

#include <iostream>
#include <cmath>

using namespace std;

long factorial(int n){
  long ans = 1;
  for (int i=1; i<=n; ++i)
     ans = ans*i;
  return ans;
 }
int main()
{
  cout << "n\tn!" << endl << "----------------" << endl;
  for (int n=0;  n<=5;  n++)
    cout << n << "\t" << factorial(n) << endl;
  return 0;
}


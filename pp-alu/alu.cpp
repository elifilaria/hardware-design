#include <iostream>
#include "blogic.H"
using namespace std;

int alu (bool F_0, bool F_1, bool INVA, bool ENA, bool ENB, bool carry_in, bool A, bool B)
{
	bool output = bor(band(band(band(B, ENB), bxor(band(A, ENA), INVA)), band(bnot(F_0), bnot(F_1))), 
			band(bor(bxor(band(A, ENA), INVA), band(B, ENB)), band(bnot(F_0), F_1)), 
			band(bnot(band(B, ENB)), band(F_0, bnot(F_1))), 
			band(bxor(carry_in, bxor(band(B, ENB), bxor(band(A, ENA), INVA))), band(F_0, F_1)));

	bool carry_out = bor(band(band(F_0, F_1), bxor(band(A, ENA), INVA), band(B, ENB)), 
			band(band(F_0, F_1), bxor(band(B, ENB), bxor(band(A, ENA), INVA)), carry_in));


	int result;
	if (carry_out == 0 && output == 0)
		result = 0;
	else if (carry_out == 1 && output == 1)
		result = 3;
	else
		result = 2;
	return result;

} 

int main()
{
	int input = alu(0, 0, 0, 1, 1, 0, 1, 0);
	cout << input << endl;
	int input2 = alu(1, 1, 0, 1, 1, 1, 1, 1);	
	cout << input2 << endl;
	int input3 = alu(0, 1, 1, 0, 1, 0, 0, 1);
	cout << input3 << endl;
}

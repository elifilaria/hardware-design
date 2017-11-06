#include <iostream>
#include "blogic.H"
using namespace std;

int alu (bool f0, bool f1, bool inva, bool ena, bool enb, bool c_i, bool a, bool b)
{
	bool output = bor(band(band(band(b, enb), bxor(band(a, ena), inva)), band(bnot(f0), bnot(f1))), 
			band(bor(bxor(band(a, ena), inva), band(b, enb)), band(bnot(f0), f1)), 
			band(bnot(band(b, enb)), band(f0, bnot(f1))), 
			band(bxor(c_i, bxor(band(b, enb), bxor(band(a, ena), inva))), band(f0, f1)));

	bool carry_out = bor(band(band(f0, f1), bxor(band(a, ena), inva), band(b, enb)), 
			band(band(f0, f1), bxor(band(b, enb), bxor(band(a, ena), inva)), c_i));


	int result;
	if (carry_out == 0 && output == 1)
		result = 2;
	else if (carry_out == 1 && output == 1)
		result = 3;
	else if (carry_out == 1 && output == 0)
		result = 1;
	else
		result = 0;
	return result;

} 

void print_call (bool f0, bool f1, bool inva, bool ena, bool enb, bool c_i, bool a, bool b)
{
	cout << "alu(" << f0 << ", " << f1 << ", " << inva << ", " << ena << ", " << enb << ", " << c_i << ", " << a << ", " << b << ") --> " << alu(f0, f1, inva, ena, enb, c_i, a, b) << endl;
	
}

void print_section (bool f0, bool f1, bool inva, bool ena, bool enb)
{
	cout << "F0=" << f0 << ", " << "F1=" << f1 << ", " << "INVA=" << inva << ", " << "ENA=" << ena << ", " << "ENB=" << enb << endl;
    for (int c_i = 0; c_i <= 1; c_i++)
    	for (int a = 0; a <= 1; a++)
    		for (int b = 0; b <= 1; b++)
                print_call(f0, f1, inva, ena, enb, c_i, a, b);


}

void print_section_32 ()
{
    for (int f0 = 0; f0 <= 1; f0++)
        for (int f1 = 0; f1 <= 1; f1++)
            for (int inva = 0; inva <= 1; inva++)
                for (int ena = 0; ena <= 1; ena++)
                    for (int enb = 0; enb <= 1; enb++){
                        print_section(f0, f1, inva, ena, enb);
                        cout << endl;
                    }
}
int main()
{
	print_section_32();

}

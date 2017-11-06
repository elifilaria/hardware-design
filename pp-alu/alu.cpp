#include <iostream>
#include "blogic.H" //This file is included because it defines the methods AND, OR, NOT and so on
using namespace std;

//The alu function takes inputs for all control and input variables for an alu and computes both the carry_out and the output. The result is determined depending on both the carry out and the output
int alu (bool f0, bool f1, bool inva, bool ena, bool enb, bool c_i, bool a, bool b)
{
	//The output and the carry out are determined separately because they both affect the result of this function
	//The output function returns the output value of a 1-bit ALU using the parameters as control and input lines
	bool output = bor(band(band(band(b, enb), bxor(band(a, ena), inva)), band(bnot(f0), bnot(f1))), 
			band(bor(bxor(band(a, ena), inva), band(b, enb)), band(bnot(f0), f1)), 
			band(bnot(band(b, enb)), band(f0, bnot(f1))), 
			band(bxor(c_i, bxor(band(b, enb), bxor(band(a, ena), inva))), band(f0, f1)));

	//The carry_out function returns the carry out value of a 1-bit ALU using the parameters as control and input lines
	bool carry_out = bor(band(band(f0, f1), bxor(band(a, ena), inva), band(b, enb)), 
			band(band(f0, f1), bxor(band(b, enb), bxor(band(a, ena), inva)), c_i));


	int result; //The result is the binary representation of the output (represented of the left side) and carry out (represented on the right side)
	if (carry_out == 0 && output == 1)
		result = 2; //(1 0) represents the number 2 in binary
	else if (carry_out == 1 && output == 1)
		result = 3; //(1 1) represents the number 3 in binary
	else if (carry_out == 1 && output == 0)
		result = 1; //(0 1) represents the number 1 in binary
	else
		result = 0; //(0 0) represents the number 0 in binary
	return result;

} 

//print_call prints alu(f0, f1, inverse a, enable a, enable b, carry in, a, b) --> decimal value for the evaluation of the alu function given inputs
void print_call (bool f0, bool f1, bool inva, bool ena, bool enb, bool c_i, bool a, bool b)
{
	cout << "alu(" << f0 << ", " << f1 << ", " << inva << ", " << ena << ", " << enb << ", " << c_i << ", " << a << ", " << b << ") --> " << alu(f0, f1, inva, ena, enb, c_i, a, b) << endl;
	
}

//print_section prints all possibilities of input combinations and the results they would produce making use of the previously defined print_call function  
void print_section (bool f0, bool f1, bool inva, bool ena, bool enb)
{
	cout << "F0=" << f0 << ", " << "F1=" << f1 << ", " << "INVA=" << inva << ", " << "ENA=" << ena << ", " << "ENB=" << enb << endl; //section label helps the user follow various combinations of control variables and their outputs
    for (int c_i = 0; c_i <= 1; c_i++)
    	for (int a = 0; a <= 1; a++)
    		for (int b = 0; b <= 1; b++)
                print_call(f0, f1, inva, ena, enb, c_i, a, b);


}

//print_section_32 loops around all possible control variable combinations and prints all 256 related results making use of previously defined print_section and print_call functions 
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

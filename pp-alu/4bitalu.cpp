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

//The fourbitalu function prints out the result of each ALU in a 4-bit format according to the values used as control and input lines. This function is based on the main alu function
void fourbitalu()
{

	bool f0, f1, inva, ena, enb, c_i, a0, b0, a1, b1, a2, b2, a3, b3; //The control line variables are boolean inputs that are cin'ed by the user because there would be too many possibilities to generate if we wanted
  //generate all possible outputs of a 4-bit ALU
	int c_o0, c_o1, c_o2, c_o3, out0, out1, out2, out3; //The carry_out of the least significant bit (c_o0) which is the cary out of the first alu (alu0) will be used as the carry in of the next 1-bit ALU (alu1) and so on...
 //The only carry out value that will be printed at the end of this function will be the carry out of the most significant bit which will be last alu (alu3)
  cout << "Please enter your control variables: " << endl;
	cout << "F0="; cin >> f0;
  cout << "F1="; cin >> f1;
  cout << "INVA="; cin >> inva;
  cout << "ENA="; cin >> ena;
  cout << "ENB="; cin >> enb;
  cout << "CARRYIN="; cin >> c_i;
	cout << "A0="; cin >> a0;
  cout << "B0="; cin >> b0;
 	cout << "A1="; cin >> a1;
 	cout << "B1="; cin >> b1;
 	cout << "A2="; cin >> a2;
 	cout << "B2="; cin >> b2;
 	cout << "A3="; cin >> a3;
 	cout << "B3="; cin >> b3;

//The carry out of each function can be determined according to the result of the alu function
//out0 is output from alu0, out1 is output from alu1, out2 is output from alu2, out3 is output from alu3
//c_o0 is carry out from alu0, c_o1 is carry out from alu1, c_o2 is carry out from alu2, c_o3 is carry out from alu3
  	int alu0 =  alu(f0, f1, inva, ena, enb, c_i, a0, b0); //initial carry in is inputted by the user
  	if (alu0 == 0 || alu0 == 2) 
  		c_o0 = 0; 
  	else
  		c_o0 = 1;
  	if (alu0 == 0 || alu0 == 1)
  		out0 = 0;
  	else
  		out0 = 1;
  	int alu1 = alu(f0, f1, inva, ena, enb, c_o0, a1, b1); //carry out of the first 1-bit ALU is inputted in the next one as the carry in
  	if (alu1 == 0 || alu1 == 2)
  		c_o1 = 0;
  	else
  		c_o1 = 1;
  	if (alu1 == 0 || alu1 == 1)
  		out1 = 0;
  	else
  		out1 = 1;
  	int alu2 = alu(f0, f1, inva, ena, enb, c_o1, a2, b2); //carry out of the second 1-bit ALU is inputted in the next one as the carry in
  	if (alu2 == 0 || alu2 == 2)
  		c_o2 = 0;
  	else
  		c_o2 = 1;
  	if (alu2 == 0 || alu2 == 1)
  		out2 = 0;
  	else
  		out2 = 1;
  	int alu3 = alu(f0, f1, inva, ena, enb, c_o2, a3, b3); //carry out of the third 1-bit ALU is inputted in the next one as the carry in
  	if (alu3 == 0 || alu3 == 2)
  		c_o3 = 0;
  	else
  		c_o3 = 1;
  	if (alu3 == 0 || alu3 == 1) //carry out of the fourth 1-bit ALU is outputted as the carry out
  		out3 = 0;
  	else
  		out3 = 1;

    cout << endl << "Output is in the form of (Output0, Output1, Output2, Output3, Carry Out3):" << endl; //The ouput of this 4-bit ALU is in terms of the output from the lest seignificant bit to the most significant bit and the carry out of the most signigificant bit at the end
  	cout << "alu(" << f0 << ", " << f1 << ", " << inva << ", " << ena << ", " << enb << ", " << c_i << ", " << a0 << ", " << b0 << ", " << a1 << ", " << b1 << ", " << a2 << ", " << b2 << ", " << a3 << ", " << b3 << ") --> " << out0 << ", " << out1 << ", " << out2 << ", " << out3 << ", " << c_o3 << endl;

}

int main()
{
	fourbitalu();

}

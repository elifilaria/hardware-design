#include <iostream>
#include "blogic.H" //This file is included because it defines AND, OR, NOT and other logica gates
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

//The nbitalu function prints out the result of an n-bit ALU (the n is decided by the user) by computing the result of this n-bit alu where inputs A and B are inputted from the least significant bit (a0 and b0) to the most. The control and input lines are mostly inputted by the user. This function takes the main alu function as base when computing output and carry out
void nbitalu(int n)
{

	bool f0, f1, inva, ena, enb, c_i; //control line variables
	bool a[n-1]; //input B's bit values will be stored in an array of size n(the size of the ALU decided by the user)
	bool b[n-1]; //input B's bit values will be stored in an array of size n(the size of the ALU decided by the user)
	int c_o[n-1]; //carry out values will be stored in an array
	int out[n-1]; //output values will be stored in an array
	int nalu[n-1]; //result values will be stored in array (result determined with the initial alu function)

//Control line variables, f0, f1, inva, ena, enb and carry in values will be inputted by the user
	cout << "Please input your control variables: " << endl; 
	cout << "F0="; cin >> f0;
  	cout << "F1="; cin >> f1;
  	cout << "INVA="; cin >> inva;
  	cout << "ENA="; cin >> ena;
  	cout << "ENB="; cin >> enb;
  	cout << "CARRYIN="; cin >> c_i;
  	c_o[0] = c_i; //the carry in for the first alu (least significant bit) (alu0) is the carry in from the user

  	for (int i = 0; i < n; i++)
  	{
  		cout << "A" << i << "="; cin >> a[i]; //A values are inputted into the a[] array by the user
  		cout << "B" << i << "="; cin >> b[i]; //B values are inputted into the b[] array by the user
  	}

  	for (int j = 0; j < n; j++)
  	{
  		nalu[j] = alu(f0, f1, inva, ena, enb, c_o[j], a[j], b[j]); //each carry in value besides the least significant bit's, will be inputted as the previous bit's carry out value
  		if (nalu[j] == 0 || nalu[j] == 2) //we can determine the values of the carry out and output by performing alu of the given inputs and looking at the result
  			c_o[j] = 0; //we know that the carry out is 0 if the result of the alu function is 0 or 2 and 1 otherwise
  		else
  			c_o[j] = 1;
  		if (nalu[j] == 0 || nalu[j] == 1) //we know that the output is 0 if the result of the alu function is 0 or 1 and 1 otherwise
  			out[j] = 0;
  		else
  			out[j] = 1;

  	}

    cout << endl << "Output is in the form of (Output0, Output1, Output2, Output3, ... Outputn, Carry Outn):" << endl;
  	cout << "alu(" << f0 << ", " << f1 << ", " << inva << ", " << ena << ", " << enb << ", " << c_i << ", ";
  	for (int x = 0; x < n; x++)
  	{ 
  		cout << a[x] << ", "; //print the values of the A's
  		cout << b[x] << ", "; //print the values of the B's
  	}
  	cout << ") --> ";
  	for (int w = 0; w < n; w++) 
  		cout << out[w] << ", "; //print the values of the outputs
  	cout << c_o[n-1] << endl; //print the carry out of the most significant bit (last ALU (alun))

}

int main()
{
	int number; //The user input that determines how many ALUs we will need to compute
	cout << "How many bits does your ALU have? "; cin >> number;
	nbitalu(number);

}

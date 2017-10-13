//The entire code that generates a hamming code for a 2-digit (8-bit) or 4-digit (16-bit) dexadecimal value is below. 
//Author: Elif Ilaria Vitucci Yurtseven, date: started october 8th and completed October 12th.

#include <iostream>
#include <math.h>
#include <bitset> //a class that is necessary to manipulate a hexadecimal input in binary representation
#include <vector>
#include <algorithm> //necessary in reversing the vector -will be clear later-
using namespace std;


/* Hamming is the main function which takes the input value and outputs the hamming code. Since I have written this code to work both
 with 2-digit (8-bit) and 4-digit (16-bit)  hexadecimal input, the hamming function takes both a vector (which represents the binary 
 epresentation of the hexadecimal  input) and the size of the vector (the size will be either 2 or 4 according to the length of the 
 input) The size represents the size of the initial input (so either 2-digit or 4-digit). 
 The output of the function is also a vector of integers because it is the 21-bit hamming code.*/
vector<int> hamming (int size, vector<int> v) 
{
	int pb ; //pb is declared here and will be assigned on line 27, it calculates the bits that are going to be parity bits. This calculation is done by assuming that the first PB will be in placement 0, PB2 will be in placement 1, PB4 will be in placement 3 and so on. This is because the bitset type that holds the binary hamming code value starts from placement 0.  
	int skips; // skips calculates the skips that each parity bit will skip in order to check the correct bits. skips is assigned on line 26. PB1 (pb at placement 0) will check 2 numbers(so check the second number), then check the 4th bit and so on. 
	int counter2; // counter2 is needed to count the total bits and determine whether the pb should be 0 or 1.
	int limit; // limit is assigned on line 29 and is necessary to make sure that the parity bits do not check further than the number of bits that the hamming code will generate.

/* The way the function works is by grouping the numbers according to which parity bit is being checked for and skipping the numbers in between. */
	for (int n = 0; n <= size; n++) // variable n simply makes sure to check every bit within the size of the input
	{
		skips = (pow(2, (n+1))); //explained on line 20
		pb = ((pow(2, n))-1); //explained on line 19
		counter2 = 0; // explained on line 21
		limit = ((pow(2,size))+size); //this will give us the size of the hamming code that will be generated. 
		for (int i = 0; i < limit+1; i+=skips) //This for loop is iterating through the skips within the length of the hamming code that will be generated. For PB1(at placement 0) it will be every (because the skips =1), for PB2(at placement 1) it will be every other two and so on. 
		{
			int counter = 0; //counter is the counter within the function that counts the number of 1's in the inner function (as each parity bit checks once) and gives the value to counter2.
			int f = pb + i; // decides which pb and which i the function is at, in order to feed it to j and calcualate the relative pb.
			for (int j = f; j <=(f + pb); j++) //this foor loop iterated through how many numbers should be grouped togeter. For PB1 (placement 0) it will be every other, for PB2 (placement 1) it will be every other 2, for PB4(placement 3) it will be every other 4 and so on. Sine it starts from j and moves up to f+pb, it makes sure that the pb is included in the count of the groups. 
			{
				if(j >= limit+2)
					break; // if the parity bits are checking beyond the number of bits that will be generated with the addition of the parity bits, the function will stop looping.
				counter += v[j]; //counter is taking the values that are in the bits that are being checked by a specific parity bit. If the total number is even the PB will be determined as zero on line 43.
			}
		counter2 += counter; //counter2 adds value collected by counter until one parity bit has been determined and then it is set back to zero on line 28 before the loop for each PB.
		}
		if (counter2 % 2 == 0) //if counter2 is an even number, it means that there is an even number 1's in the 16-bit code and the relevant PB should be 0, else, it should be 1.
			v[pb] = 0; //the relative parity bit is being set to 0 if the total count of 1's in the 8 or 16-bit code was an even number.
		else
			v[pb] = 1; //the relative parity bit is being set to 1 if the total count of 1's in the 8 or 16-bit code was an odd number.
	}

	return v;
}
//The hamming function has returned a 12-bit (if the input was 2-digit) or 21-bit (if the input was 4-digit) value which is stored within a vector.


/* The convert function mathematically converts the 12-bit or 21-bit binary hamming code that has been generated into first a decimal and then a hexadecimal value.  */
void convert (int size, vector<int> v) //This function takes the size of the vector (containing the hamming code) and the vector and converts the binary into a hexadecimal. The reason why it takes both size and the vector as input it because this code is valid both for 8-bit and 16-bit input. 
{
	long int sum = 0; //sum will be the decimal value of the binary hamming code that has been inputted
	int askey; // askey is the variable that will decide whether the input is a number or a letter according to their ASCII value -this will become clear below-
	char hexa[100]; //this array will contain the final hexadecimal code once the value from the binary hamming code are converted into hexadecimal and are not numbers but characters.
	int w = 1; //w represents the position of every digit in the hexadecimal code that is being outputted
	reverse(v.begin(), v.end()); // The hamming code is being reversed because the transformation needs to be from the right most 4 digits moving towards the left in order to make the conversion correct.
	for (int f = 0; f <= ((pow(2,size))+size); f++) //this loops around each position in the binary hamming code 
	{
		sum += ((pow(2, f))*v[f]); //creates the sum by adding the value of 2 to the power of each position where there is a 1 in the binary hamming code
	}

	while (sum != 0) //this while loop divides the decimal equivalence of the binary hamming code (sum) by 16 and calculates
	{
		askey = sum % 16; //askey is the remainder of each division by 16

		if (askey < 10) //if this number is smaller than 10 it is added to the number 48(which is the ASCII code for 0)which means it will remain a number
			askey += 48;
		else
			askey += 55; //if askey (the remainder) is larger than 10 it will be added to the 55 so that it will start being numbered as letters from A to F (the ASCII code for A is 65 so 10 would become 10+55 = 65 which corresponds to the letter A)

		hexa[w++] = askey; //the corresponding characters in the character array hexa are being placed with the ASCII codes that are being generated
		sum /= 16; //the sum is divided by 16 every time and this process will continue until the sum is 0
	}
		cout << "The hexadecimal value of your Hamming code is: ";
		for (int j= w-1; j>0; j--) //this loop prints the values in the character array which is now holding the hexadecimal code for the binary hamming code that was inputted
			cout << hexa[j];

	cout << endl;

}


/* The decision function decides whether the input is a 2-digit (8-bit) or 4-digit (16-bit) hexadecimal value and adds the parity bits that are initially set to 0 such that the hamming code can be generated and converted into hexadecimal*/
void decision(int d, int x) //this function takes two integers as input, d is the length of the x that is being inputted
{
	if (d == 8) //if the length is 8 bits
	{
		bitset<8> b(x); //the input is being translated to a bitset of length 8, bitset is a C++ class that transforms a hexadecimal number into a binary and stores it 
		b.to_ulong(); //bitset b is being transformed into an integer
		vector<int> v (8); //a vector of length 8, because the bitset is of length 8 is being created
		int j = 0;
		for (int i = 7; i >= 0; i--) //each value in bitset if the alue is one the corresponding value in the vector is also set to one, and if it zero the corresponding value is also set to zero. This process is done reversing the bits from bitset because the way the class bitset works is by storing the 8 or 16-bit value in reverse. This number is 7 instead of 8 even though the size is 8 because 0 is included
		{
			if(b[i] == 1) //if the bit in bitset is one the corresponding value in v is set to 1, the same for zero.
				v[j] = 1;
			else
				v[j] = 0; 
			j++;
		}

		for (int i = 0; i <= log2(v.size()); i++) //this for loop places the parity bits into their right places. i loops from 0 to log2(the size of v) because parity bits will be placed in 4 (it will be 4 when i loops from 0 to 3 because 0 is included) places is the initial input was 8-bit and in 5 places if the initial input was 16-bit
		{
			v.insert((v.begin() + (pow(2, i))-1), 0); //v.insert and v.begin are member functions of the vector class in C++. This line is adding a value 0, and shifting all the numbers to the right of that 0 by 1 so each place that are the parity bits. The places are calculated according to the size of the input
		}

		vector<int> v2 = hamming (log2(v.size()), v); //the decision function calls the hamming function to create a hamming code of the input

		convert (log2(v2.size()),v2); //the decision function call the convert function to convert the generated hamming code into hexadecimal

	}
	else if (d == 16) //This part of the conditional is the same as the if part of the conditional, but it works if the hexadeciaml value entered by the user was a 4-digit (16-bit) code
	{
		bitset<16> b(x);
		b.to_ulong();
		vector<int> v (16);
		int j = 0;
		for (int i = 15; i >= 0; i--)
		{
			if(b[i] == 1)
				v[j] = 1;
			else
				v[j] = 0;
			j++;
		}

		for (int i = 0; i <= log2(v.size()); i++)
		{
			v.insert((v.begin() + (pow(2, i))-1), 0);
		}

		vector<int> v2 = hamming (log2(v.size()), v);

		convert (log2(v2.size()),v2);

	}
	else
	{
		cout << "Your entry is not an 2-digit or 4-digit hexadecimal value." << endl; // if the function is not able to manipulate the input it will decide that is neither a 2-digit nor a 4-digit hexadecimal value
	}
}

int main() 
{
	cout<< "Please enter an 2-digit or 4-digit hexadecimal value: ";
	int x; //this is the input that is being given by the user and being stored in the variable x
	cin >> hex >> x;
	int num = x; //Because of how cin>> hex works we cannot manipulate the values of x immediately, hence we needed to put it in a variable

	int digits = 0; //digits will give us the power that we need to raise the number 2 in order to get the full length of the input, hence digits = the size of the input which we need for the rest of our functions
	while(num){ //we are dividing num (the input x) by as many times as it is mathematically possible to get its size
		num /= 2;
		digits++;
	}

	decision(digits, x); //this functions calls decision which decides whether the input is 2-digit(8-bit) or 4-digit(16-bit) with the size that is calculated right up and stored as digits, this will call hamming and convert and give us the desired output which is a hexadecimal value

}
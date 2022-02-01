//Lab 1
//COSC130
//This program performs basic arithmetic.
//Zachery Creech
//1/17/2019

#include <iostream>
#include <string>

using namespace std;

int CharToInt(char v);
char IntToChar(int v);
int StringToInt(string val);
string IntToString(int val);

int main(int argc, char* argv[])
{
	string sresult;
	int left;
	int right;
	char op;

	if(4 != argc)
	{
		printf("Usage: %s <left> <op> <right>\n", argv[0]);
		return -1;
	}

	left = StringToInt(argv[1]);
	right = StringToInt(argv[3]);
	op = argv[2][0];

	switch(op)
	{
		case 'x':
			sresult = IntToString(left * right);
			break;
		case '/':
			sresult = IntToString(left / right);
			break;
		case '+':
			sresult = IntToString(left + right);
			break;
		case '-':
			sresult = IntToString(left - right);
			break;
		case '%':
			sresult = IntToString(left % right);
			break;
		default:
			sresult = IntToString(left);
			break;
	}

	printf("%d %c %d = %s\n", left, op, right, sresult.c_str());

	return 0;
}

int CharToInt(char v) //convert char to int
{
	int newInt = v - '0';
	return newInt;
}

char IntToChar(int v) //convert int to char
{
	char newChar = v + '0';
	return newChar;
}

int StringToInt(string val) //convert string to int
{
	bool negative = false;
	
	if(val[0] == '-') //checks for negative sign
	{
		negative = true;
		string newString = "";

		for(unsigned int i = 1; i < val.size(); i++) //builds new string without negative sign for easier manipulation
			newString += val[i];

		val = newString; //sets val to positive version of the string
	}

	int newInt = 0;

	for(unsigned int i = 0; i < val.size(); i++) //each character is changed from char to int using ASCII arithmetic
		newInt = (val[i] - '0') + (newInt * 10);
	
	if(negative) //if is negative, changes final int to be negative
		newInt *= -1;
	
	return newInt;
}

string IntToString(int val) //convert int to string
{
	bool negative = false;

	if(val < 0) //checks for negative number
	{
		val *= -1; //makes val positive to avoid errors when using %
		negative = true;
	}

	string newString = "";

	do {
		newString += ((val % 10) + '0'); //do while creates new string but backwards, if 0 then sets to 0 and ends
		val /= 10; //removes end of the number before starting over
	} while(val > 0);
	
	if(negative) //appends negative sign to end
		newString += '-';
	
	string actualString = "";

	for(int i = newString.size() - 1; i >= 0; i--) //reverses the backwards number
		actualString += newString[i];

	return actualString;
}

//Lab 3
//COSC130
//This program adds, subtracts, and multiplies
//two user-input numbers using bit operations.
//Zachery Creech
//1-31-2019

#include <iostream>

using namespace std;

int sign(int);
int twos(int);
int add(int, int);
int sub(int, int);
int mul(int, int);

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		printf("Usage: %s <num> <op> <num>\n", argv[0]);
		return -1;
	}

	int left;
	int right;
	char op;
	int result;

	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);

	switch(op)
	{
		case '+':
			result = add(left, right);
			break;
		case '-':
			result = sub(left, right);
			break;
		case 'x':
			result = mul(left, right);
			break;
		default:
			printf("Unknown operation '%c'\n", op);
			return -2;
	}

	printf("%d %c %d = %d\n", left, op, right, result);

	return 0;
}

int sign(int val) //checks the last (left-most) bit for sign, 1 = negative 0 = positive
{
	val >>= 31;
	return val & 1;
}

int twos(int val) //converts number to its twos-complement
{
	return add(~val, 1);
}

int add(int left, int right) //adds two numbers together using bit operations
{
	int carry = 0;
	int sum = 0;

	for(int i = 0; i < 32; i++)
	{
		int l = (left >> i) & 1;
		int r = (right >> i) & 1;
		int s = l ^ r ^ carry;
		carry = (l & r) | (r & carry) | (l & carry);
		sum = sum | (s << i);
	}
	return sum;
}

int sub(int left, int right) //subtracts right number from the left, uses add() and converts left to a negative with twos()
{
	return add(left, twos(right));
}

int mul(int left, int right) //multiplies two numbers together through repeated addition
{
	bool negative; //if this ends up being true, convert the product to a negative
	if(sign(left) || sign(right)) //checks if either number is negative
		negative = true;
	if(sign(left) && sign(right)) //checks if both numbers are negative; if so, product must be positive
		negative = false;
	
	if(sign(left)) //if left is negative, converts it to a positive
		left = twos(left);
	if(sign(right)) //if right is negative, converts it to a positive
		right = twos(right);
		
	int i = right; //sets the number of iterations equal to the multiplier
	int product = 0; 
	while(i != 0) //adds the left number to 0 a number of times equal to the multiplier
	{
		product = add(product, left);
		i = sub(i, 1);
	}
	
	if(negative) //if product should be negative, make product negative
		product = twos(product);

	return product;
}

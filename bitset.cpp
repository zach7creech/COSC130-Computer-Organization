//Lab2
//COSC130
//This program takes user input to manually edit the bits of an integer.
//Any number of integers can be stored by the program at one time, but it
//will always store at least one. The default value for that integer is 0.
//Zachery Creech

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class BITSET
{
	vector<int> intvec;
public:
	BITSET()
	{
		intvec.push_back(0);
	}
	bool test(int) const;
	void set(int);
	void clear(int);
	string to_binary(unsigned int) const;
};

int main()
{
	BITSET bs;
	char com; //stores what command the user inputs
	int inSet; //index or set; index for test(), set(), clear(); set for to_binary()
	while(com != 'q') //while user does not want to quit
	{
		printf("Enter command: ");
		scanf("%c", &com); //gets command from user
		if(com != 'q')
		{
			scanf("%d", &inSet); //if the user does not want to quit, program reads in specific index/set pertaining to user command
			switch(com)
			{
				case 't': //test function
					if(bs.test(inSet)) //test() returns a boolean, if returns true outputs 1, if returns false outputs 0
						printf("%d\n", 1);
					else
						printf("%d\n", 0);
					break;
				case 's': //set function
					bs.set(inSet);
					break;
				case 'c': //clear function
					bs.clear(inSet);
					break;
				case 'p': //print function
					printf("%s\n", bs.to_binary(inSet).c_str());
					break;
				default:
					break;
			}
		}
		while(getchar() != '\n'); //prevents printf() from printing random '\n' characters (it seems random, I don't fully understand it)
	}
}

bool BITSET::test(int index) const
{
	unsigned int set = index / 32; //dividing index by 32 returns a truncated int corresponding to the correct set
	if(set + 1 > intvec.size()) //if set does not exist, return false
		return false;
	int bit = index - (set * 32); //finds actual bit from given index by subtracting the indices of lower-indexed integers
	return (intvec.at(set) >> bit) & 1;
}

void BITSET::set(int index)
{
	unsigned int set = index / 32;
	if(set + 1 > intvec.size()) //if set does not exist, add a new one
		intvec.push_back(0);
	int bit = index - (set * 32);
	intvec.at(set) |= (1 << bit);
}

void BITSET::clear(int index)
{
	unsigned int set = index / 32;
	if(set + 1 > intvec.size()) //if set does not exist, end function and do nothing
		return;
	int bit = index - (set * 32);
	intvec.at(set) &= ~(1 << bit);
	for(unsigned int i = intvec.size() - 1; i > 0; i--) //after clearing of given bit is finished, check if the set has integer value = 0 starting from the last stored set and remove it
	{
		if(intvec.at(i) == 0)
			intvec.pop_back();
		else
			break;
	}
}

string BITSET::to_binary(unsigned int set) const
{
	string binNum = "";
	if(set + 1 > intvec.size()) //if set does not exist, return the empty string
		return binNum;
	int index = set * 32;
	for(int i = index; i < index + 32; i++) //builds the string representation of the binary number backwards
	{
		if(i % 4 == 0 && i != 0) //adds spaces every four bits
			binNum += ' ';
		if(test(i)) //if test() returns true, add '1' to string
			binNum += '1';
		else
			binNum += '0'; //else add '0'
	}
	string flipBinNum = "";
	for(int i = binNum.size() - 1; i >= 0; i--) //flips the backward binary number to correct orientation
		flipBinNum += binNum[i];
	return flipBinNum;
}	

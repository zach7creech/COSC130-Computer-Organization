//Lab 8
//C++ file for testing lab8.S RISC-V
//COSC130
//Zachery Creech
//3-5-2019

#include <iostream>

using namespace std;

struct PERSON
{
	char name[51];
	int age;
	char gender;
};

extern "C"
{
	PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
	int Median(const int array[], int array_size, int *buffer);
}


//PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
//int Median(const int array[], int array_size, int *buffer);

int main()
{
	//For testing Median()
	/*
	const int array[7] = {7,2,-3,-2,100,3,0};
	int array_size = 7;
	int *buffer = new int[7];
	int median;
	median = Median(array, array_size, buffer);
	cout << median << '\n';
	*/
	// For testing Search()
	/*
	PERSON fred = {"fred flinstone                                    ", 56, 'm'};
	PERSON meguka = {"meguka                                            ", 13, 'f'};
	PERSON zerotwo = {"02                                                ", 17, 'f'};
	PERSON heathen = {"heathen richards                                  ", 19, 'm'};
	PERSON people[4] = {fred, meguka, zerotwo, heathen};
	PERSON *match;
	match = Search(people, 4, "02                                                ", 17, 'f');
	if(match != nullptr)
		cout << match->name << ' ' << match->age << ' ' << match->gender << '\n';
	else if(match == nullptr)
		cout << "No match.\n";
	*/
	return 0;	
}
/*
PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender)
{
	bool match = false;
	bool nameFail = false;
	int matchptr;
	for(int i = 0; i < num_people; i++)
	{
		if(people[i].age == age)
		{
			if(people[i].gender == gender)
			{
				for(int j = 0; j < 51; j++)
				{
					if(people[i].name[j] != name[j])
	 				{
						nameFail = true;
						break;
					}
				}
				if(!nameFail)
				{	
					match = true;
					matchptr = i;
				}
			}
		}
		if(match)
			return &people[matchptr];
	}
	return nullptr;
}
*/
/*
int Median(const int array[], int array_size, int *buffer) *buffer will contain sorted list
{
	bool isEven = false;
	if(array_size % 2 == 0)
		isEven = true;
	int lastMin = array[0];
	for(int i = 0; i < array_size; i++)
	{
		if(lastMin > array[i])
			lastMin = array[i];
	}
	int max = lastMin + 1;
	for(int i = 0; i < array_size; i++)
	{
		if(max < array[i])
			max = array[i];
	}
	int bufInd = 0;
	int nextMin = max;
	for(int i = 0; i < array_size; i++)
	{
		if(lastMin == array[i])
		{
			buffer[bufInd] = lastMin;
			bufInd++;
		}
		if(array[i] > lastMin && array[i] <= nextMin)
			nextMin = array[i];
		if(i + 1 == array_size && bufInd != array_size)
		{
			i = -1;
			lastMin = nextMin;
			nextMin = max;
		}
	}
	//for(int i = 0; i < array_size; i++)
	//	cout << buffer[i] << '\n';
	int median;
	if(isEven)
		median = (buffer[array_size / 2] + buffer[(array_size / 2) - 1]) / 2;
	else
		median = buffer[array_size / 2];
	return median;
}*/

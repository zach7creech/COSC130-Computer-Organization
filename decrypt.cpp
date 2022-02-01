//Lab 6
//This program decrypts a binary file given
//two keys; a data key and an index key.
//COSC130
//Zachery Creech

#include <stdio.h>

int main(int argc, char *argv[])
{
	if(argc < 4)
	{
		printf("Usage: %s <file> <dkey> <nkey>\n", argv[0]);
		return -1;
	}

	char dkey; //stores the data key
 	sscanf(argv[2], "%c", &dkey);
	int nkey; //stores the index key
	sscanf(argv[3], "%d", &nkey);
	
	FILE *fin; 
	fin = fopen(argv[1], "rb");
	fseek(fin, 0, SEEK_END);
	int size = ftell(fin); //finds the size of the binary file
	int numChar = size / 8; //each encrypted char is made up of 8 bytes in the file, so the total bytes in the file / 8 gives the number of encrypted chars
	char *message = new char[numChar]; //creates and allocates memory for storage of decrypted message

	for(int i = 0; i < size; i += 8) //goes through the whole file, increments by 8 each time because the first byte of each encrypted char starts at index 0, 8, 16, etc.
	{
		int curChunk = i / 8; //for printing error message if current chunk's decrypted index is outside acceptable values
		char data; //to store decrypted char
		int index; //to store decrypted index
		fseek(fin, i, SEEK_SET); //goes to first byte of 8 byte encrypted char
		fread(&data, 1, 1, fin); //gets first byte
		fseek(fin, 3, SEEK_CUR); //skips the 3 "padding" bytes 
		fread(&index, 1, 4, fin); //gets the last 4 bytes that make up the decrypted index
		data ^= dkey; //decrypts char with given data key
		index ^= nkey; //decrypts index with given index key
		if(index > numChar || index < 0) //error for if decrypted index is outside acceptable values
		{	
			printf("Error decoding chunk %d, decoded index %d, but range of chunks is [0 - %d].\n", curChunk, index, numChar);
			return -2;
		}
		message[index] = data; //stores decrypted char in appropriate index
	}

	printf("%s", message);

	fclose(fin);
	
	delete[] message;

	return 0;
}

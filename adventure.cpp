//Lab 5
//COSC130
//This program reads in a file that represents rooms in a text-adventure game
//and allows the user to traverse the rooms. The user can also "look" at the rooms
//to get a description of them and find valid next rooms to go to.
//Zachery Creech
//2-15-2019

#include <cstdio>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Room
{
	string name;
	string descr;
	string dirRoom;
};

int scanOrCopy(string, bool, Room* = nullptr); //Room* has default value because copying requires the pointer but scan must run first to create the pointer
string findExits(Room*, int); 
int findNextRoom(Room*, int, char);

int main(int argc, char* argv[])
{
	if(argc < 2)
	{	
		printf("Usage: %s <filename>", argv[0]);
		return -1;
	}

	int numRooms = scanOrCopy(argv[1], false); //only scans for room number
	Room *roomptr = new Room[numRooms + 1]; //allocates memory for the correct number of rooms. + 1 is because roomptr[0] cannot be accessed/edited for some reason
	scanOrCopy(argv[1], true, roomptr); //copies data from file
	char command;
	int curRoom = 1; //room indices start from one
	int nextRoom = 1; //stores what the room to move to will be

	while(command != 'q') //constantly asks for user input until user inputs 'q' to quit
	{
		string curName = roomptr[curRoom].name; //puts the name into a more clear variable for further use
		string curDescr = roomptr[curRoom].descr; //puts description ' ' ' '
		string curExits = findExits(roomptr, curRoom); //puts exits ' ' ' '
		printf("> ");
		scanf(" %c", &command);
		switch(command) //chooses correct thing to do based on user command
		{
			case 'l': //look
				printf("%s\n%s\n\nExits:%s\n", curName.c_str(), curDescr.c_str(), curExits.c_str()); //prints the appropriate information for current room
				break;
			case 'n': //north
				nextRoom = findNextRoom(roomptr, curRoom, command); //based on current room decides if input direction is valid
				if(nextRoom == -1) //findNextRoom returns -1 if the input direction is not valid
					printf("You can't go NORTH!\n");
				else
					printf("You moved NORTH.\n");
				break;
			case 'e': //east
				nextRoom = findNextRoom(roomptr, curRoom, command); 
				if(nextRoom == -1)
					printf("You can't go EAST!\n");
				else
					printf("You moved EAST.\n");
				break;
			case 's': //south
				nextRoom = findNextRoom(roomptr, curRoom, command);	
				if(nextRoom == -1)
					printf("You can't go SOUTH!\n");
				else
					printf("You moved SOUTH.\n");
				break;
			case 'w': //west
				nextRoom = findNextRoom(roomptr, curRoom, command);
				if(nextRoom == -1)
					printf("You can't go WEST!\n");
				else
					printf("You moved WEST.\n");
				break;
			case 'q': //quit
				break;
			default:
				break;
		}
		if(nextRoom != -1 && command != 'l') //curRoom does not need to change if user wants to look or inputs an invalid direction
			curRoom = nextRoom + 1;
	}

	delete[] roomptr; //frees memory from roomptr
	
	return 0;
}

int scanOrCopy(string file, bool copy, Room *roomptr) //can scan a file of rooms to get number of rooms or copy the data from the file into Room pointer
{
	//boolean comparisons containing copy only execute when the program is copying the data from the file
	ifstream fin;
	fin.open(file);
	int numRooms = 0;
	string line;
	string curName = "";
	string curDescr = "";
	string curDir = "";
	bool singleTitle = true; //for potential multiline titles of rooms
	while(!(fin.eof()))
	{	
		getline(fin, line); //gets first line, presumably the first line of the title of the given room
		if(line == "~") //when line = "~" the loop moves on to finding the description
		{
			line = ""; //removes "~" from line to execute next while loop
			numRooms++; //increments room number after title is successfully read, confirms existence of new room
			int descrIter = 0; //descriptions need to keep appropriate new lines, this increments to tell loop when to re-add new lines after getline
			while(line != "~")
			{
				getline(fin, line);
				if(copy && descrIter != 0 && line != "~") //adds new line when appropriate, after the first line of description and not after the last line
					curDescr += '\n';
				if(copy && line != "~") //adds line of description when approopriate
					curDescr += line;
				descrIter++;
			}
			line = ""; //removes "~" from line to execute next while loop
			while(line != "~")
			{
				getline(fin, line);
				if(copy && line != "~") //adds each "dir roomNum" line to the curDir string separated by new line for parsing later
					curDir += (line + '\n');
			}
			if(copy) //each line adds corresponding string to correct member of Room pointer
			{
				roomptr[numRooms].name = curName; 
				roomptr[numRooms].descr = curDescr;
				roomptr[numRooms].dirRoom = curDir;
			}
			singleTitle = true; //resets all flags to original state to look at next room
			curName = "";
			curDescr = "";
			curDir = "";
		}
		else if(copy)
		{
			if(singleTitle) //this always executes first
			{
				curName += line; //adds first line of title to curName
				singleTitle = false; //sets flag to false so else of this statement will execute if there happens to be another line of the room name
			}
			else
				curName += ('\n' + line);
		}
	}
	
	return numRooms; //returns int representing total number of rooms scanned, typically does not matter when function is used to copy because this has already ran once
}

string findExits(Room *roomptr, int curRoom) //finds exits for the current room and trims the room number for correct console output
{
	stringstream ss(roomptr[curRoom].dirRoom); //this was written with stringstreams when I was doing this a little differently; may be unnecessary in some respects but it works
	int numDir = 0;
	string line;
	while(getline(ss, line)) //gets number of pairs of directions contained in the string (separated by new lines)
		numDir++;
	ss.clear(); //clears the stream for ss to parse stream again
	ss.seekg(0); //back to beginning
	string exits = "";
	for(int i = 0; i <= numDir; i++) //gets each cardinal direction from each pair and puts them in a string to print to console
	{
		getline(ss, line);
		exits += ' ';
		exits += line[0]; //line[0] is the cardinal direction
	}
	return exits; //returns string of cardinal directions without room numbers
}

int findNextRoom(Room *roomptr, int curRoom, char direction) //similar to findExits() but also compares the user-input cardinal direction to available directions and returns what room, if any to go to
{
	stringstream ss(roomptr[curRoom].dirRoom);
	int numDir = 0;
	string line;
	while(getline(ss, line)) //gets number of pairs of directions
		numDir++;
	ss.clear(); //clears stream for ss to parse stream again
	ss.seekg(0);
	
	string *directions = new string[numDir]; //resizable array of the directions, size is equal to number of pairs of directions

	for(int i = 0; i < numDir; i++) //gets each pair and puts them in the array
	{	
		getline(ss, line);
		directions[i] = line;
	}
	
	int nextRoom = -1; //if user input does not match any available directions for the current room, return -1 to tell program to stay in current room
	for(int i = 0; i < numDir; i++) //goes through array and compares the cardinal directions to user-input direction
	{
		if(directions[i][0] == direction) //directions[i][0] is the cardinal direction
		{
			int fullSize = directions[i].length(); 
			string number = directions[i].substr(2, fullSize - 2); //the room number associated with a cardinal direction is always from string index 2 (after cardinal at 0 and whitespace between at 1) and str.substr() gets from there to (size of the string - 2) to get the int for next room
			stringstream numss(number); //puts the int into a stringstream
			numss >> nextRoom; //puts the int into an actual int
		}	
	}
	delete[] directions; //deletes the resizable array
	return nextRoom; //returns next room number, -1 if user-input cardinal direction does not match any of the current room's given directions
}

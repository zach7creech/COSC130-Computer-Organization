//Lab 8
//This RISC-V file contains the definition of two functions:
//Search() and Median(). They are to be used in a .cpp file.
//Search() searches through an array of PERSON structures to
//find a match for a given name, age, and gender. It returns
//a pointer to the match, or nullptr if no match. Median()
//sorts an array of integers from least to greatest into a
//buffer and then finds the median of those numbers.
//COSC130
//Zachery Creech
//3-6-2019

.section .text
.global Search

//		NOS Table for struct PERSON
//
//		Name		Offset		Size
//		char		0			51
//							   + 1
//		int			52			 4
//							   + 0
//		char		56			 1
//		57 % 4 != 0 so		   + 3
//		60 % 4 == 0	so total =	60

Search:
		li		t4, 60
		mul		t0, a1, t4 //multiply num_people * 60 for condition of for loop
		addi	t0, t0, -1 //subtract one because last good index is 60 * (elements in people[]) - 1
		li		t1, 0 //keeps track of what index in people[] loop is on, used for comparison to avoid OoB errors, follows memory location of a0
		li		t3, 51 //for checking if there is a match
		j		3f

		//starts at 2 because I thought I might need to jump back one more. I didn't and the program works now, and I'm too afraid to change it
		2:	
			sub		a0, a0, t2 //removes whatever excess memory was added in the process of checking name (a0)
			sub		t1, t1, t2 //removes whatever excess memory was added in the process of checking name (t1)
			sub		a2, a2, t2 //removes whatever excess memory was added in the process of checking name (*name)
			addi	t1, t1, 60 //t1 follows a0 to check if the next addition to memory location would go out of bounds
			bgt		t1, t0, exit //if reached end of people[] exit
			addi	a0, a0, 60 //goes to next person
		3:	
			addi	a0, a0, 52 //go to current age (a0)
			addi	t1, t1, 52 //t1 follows a0
			lw		t5, 0(a0) //t5 = current age
			beq		t5, a3, 4f //if(current age == check age) branch to check gender
			addi	t1, t1, 8 //t1 follows a0
			bgt		t1, t0, exit //if reached end of people[] exit
			addi	a0, a0, 8 //if(current age != check age) branch add enough to current person to move to next person (a0)
			j		3b //start over with next person
		4:
			addi	a0, a0, 4 //go to current gender
			addi	t1, t1, 4 //t1 follows a0
			lb		t5, 0(a0) //t5 = current gender
			beq		t5, a4, 5f //if(current gender == check gender) branch to check name
			addi	t1, t1, 4 //t1 follows a0
			bgt		t1, t0, exit //if reached end of people[] exit
			addi	a0, a0, 4 //if(current gender != check gender) add enough to current person to move to next person (a0)
			j		3b //start over with next person
		5:
			li		t2, 0 //int j = 0 //for keeping track of how many chars have been checked
			addi	a0, a0, -56 //sets person[i] back to 0: first char of name
		6:
			lb		t5, 0(a0) //t5 = current char in name
			lb		t6, 0(a2) //t6 = check char in *name
			bne		t5, t6, 2b //if name doesn't match, go to subtract current person back to first char in current name then add 60 to go to next person
			addi	t2, t2, 1 //keeps track of how much is added to name to subtract if there isn't a match or when there is a complete match
			beq		t2, t3, match //if the char count reaches 51 then there was a match
			addi	a0, a0, 1 //next char in current name
			addi	t1, t1, 1 //t1 follows a0
			addi	a2, a2, 1 //next char in *name
			j		6b
		match:
			addi	a0, a0, -50 //removes excess memory from checking name, sets back to memory address [0] of matching person
			ret
		exit:
			mv		a0, zero //returns nullptr
			ret
.global Median
Median:
		//setup
		mv		t0, a1 //t0 = array_size
		li		t1, 4 //t1 = 4
		mul		t0, t0, t1 //finds 4 * array_size
		mv		t6, t0 //puts total number of bytes in array[] into t6
		addi	t6, t6, -4 //total array size - 4 = memory address of final element; to be used when reseting for loops and current element of a0
		addi	t0, t0, -1 //subtracts one, maximum good memory address in array[] is (4 * array_size) - 1; put in t0 FOR COMPARISON
		li		t1, 0 //t1 = 0 = i counter for keeping track of current memory location in array[]
		lw		t2, 0(a0) //t2 = lastMin; lastMin = array[0]
		j		3f
		
		1:
			lw		t2,	0(a0) //lastMin = array[i]; sets t2 = to the next smallest number found
		2:
			addi	t1, t1, 4 //increments counter by one array element sizeof(int) = 4
			bgt		t1, t0, 4f //if counter exceeds array size, end for loop
			addi	a0, a0, 4 //if for loop continues, increment location in array[] by 1 element
		3:
			lw		t3, 0(a0) //loads current array[i] into t3 for comparison to lastMin (t2)
			bgt		t2, t3, 1b //if lastMin is > current array[i] then array[i] must be the next smallest number
			j		2b
		4:	
			//should only run once to set up finding maximum value in array[]
			sub		a0, a0, t6 //sets a0 (array[]) back to array[0]
			li		t1, 0 //sets counter back to zero
			mv		t4, t2 //t4 = max to find greatest number
			addi	t4, t4, 1 //adds 1 for theoretical next max; for checking array again to find actual largest
			j		7f
		5:
			lw		t4, 0(a0) //max = array[i] sets t4 = to the next largest number found
		6:
			addi	t1, t1, 4 //increments counter by one array element
			bgt		t1, t0, 8f //if counter exceeds array size end for loop
			addi	a0, a0, 4 //if for loop continues, increment location in array[] by 1 element
		7:
			lw		t3, 0(a0) //loads current element of array[] into t3 for comparison to max (t4)
			blt		t4, t3, 5b //if max < current array[i] then array[i] must be the next biggest number
			j		6b
		8:
			//runs once to set up for loop that sorts array[] into *buffer
			sub		a0, a0, t6 //sets a0 (array[]) back to array[0]
			li		t1, 0 //sets counter back to zero
			li		t5, 0 //t5 = buffer index, starts equal to zero
			mv		a4, t4 //sets nextMin = max; ran out of t registers and didn't feel like using s registers
			j		9f
		12:
			addi	a0, a0, 4 //moves to next element in array[i]
		9:
			lw		t3, 0(a0) //loads array[i] into t3 for comparison to lastMin (t2), finding all instances of current minimum to add to buffer
			bne		t2, t3, 10f //jump to next conditional if array[i] != last minimum
			//modifying *buffer if array[i] == last minimum
			sw		t2, 0(a2)
			addi	t5, t5, 4 //add 4 to buffer index to check if at end of *buffer
			bgt		t5, t0, 13f //if at end of buffer, program is finished sorting so jump to finding median
			addi	a2, a2, 4 //if not move to next element in *buffer
		10:	
			//next condition
			ble		t3, t2, 11f //if array[i] < lastMin then can skip next conditional and go straight to deciding whether or not to reset loop
			//next condition
			bgt		t3, a4, 11f //if array[i] > nextMin then skip to next conditional. If not, then that means the next smallest number has been found and needs to be stored in nextMin (a4)
			mv		a4, t3 //loads array[i] into nextMin
		11:
			addi	t1, t1, 4 //if(i == array_size) if loop is about to end, start over
			blt		t1, t0, 12b //if(i < array_size) continue loop
			//reset for loop then search for next smallest number to fill *buffer with
			li		t1, 0 //resets counter
			mv		t2, a4 //lastMin = nextMin new minimum for next loop
			mv		a4, t4 //nextMin = max finding new next minimum
			sub		a0, a0, t6 //resets array[] to array[0]	
			j		9b
		13:
			sub		a2, a2, t6 //sets buffer memory address back to buffer[0]
			li		t1, 2
			rem		t0, a1, t1 //array_size % 2 to decide if the array has an even or odd number of elements
			div		t2, a1, t1 //t2 is index of median if odd array OR index of second of two middle elements if even array
			li		t1, 4
			mul		t2, t2, t1 //gives correct memory offset (memory offset of each element = 4 * index)
			add		a2, a2, t2 //moves memory location of a2 to correct index for odd array OR second of two middle elements for even array
			beq		t0, zero, 14f //if array_size % 2 == 0; even number of elements so needs to find middle two elements and divide by 2
			lw		a0, 0(a2) //else move median to a0 for return
			ret
		14:
			lw		t3, 0(a2) //t3 now stores second of middle two elements
			addi	a2, a2, -4 //first of middle two elements is at t3 - 1 
			lw		t4, 0(a2) //t4 now stores first of middle two elements
			add		t3, t3, t4 //adds the middle elements together
			li		t1, 2 
			div		t4, t3, t1 //divides sum of middle elements by 2
			mv		a0, t4 //moves median to a0 for return
			ret

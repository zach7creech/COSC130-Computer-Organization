//Lab 7
//This program performs basic arithmetic based on command line 
//arguments. Supports addition, subtraction, multiplication,
//division, and modulo.
//COSC130
//Zachery Creech
//2-28-2019

.section .rodata
output: .asciz "Result: %d %c %d = %d\n"
not_op: .asciz "Unknown operator '%c'\n"
integer_scan: .asciz "%d"
char_scan: .asciz "%c"
not_enough: .asciz "Not enough arguments.\n"
too_many: .asciz "Too many arguments.\n"

.section .text
.global addition
addition:
		add		a0, a0, a1
		ret
.global subtract
subtract:
		sub		a0, a0, a1
		ret
.global multiply
multiply:
		mul		a0, a0, a1
		ret
.global divide
divide:		
		beq		a1, zero, 8f //if right operator a1 == 0, set result a0 to -1 and return to main
		div		a0, a0, a1
		ret
		8:
			li		a0, -1
		ret
.global modulo
modulo:
		beq		a1, zero, 8f //if right operator a1 == 0, set result a0 to -1 and return to main
		rem		a0, a0, a1
		ret
		8:
			li		a0, -1
		ret
.global main
main:
		//Allocate memory on the stack
		addi	sp, sp, -64
		sd		ra, 0(sp)

		//checking that argc (a0) is exactly 4
		li		t0, 4
		blt		a0, t0, not_enough_arguments
		bgt		a0, t0, too_many_arguments

		//saving argv[1-3] into save registers
		sd		s0, 8(sp) //left
		sd		s1, 16(sp) //op
		sd		s2, 24(sp) //right

		ld		s0, 8(a1)
		ld		s1, 16(a1)
		ld		s2, 24(a1)

		//sscanf(argv[1], "%d", &left)
		mv		a0, s0
		la		a1, integer_scan
		addi	a2, sp, 32
		call	sscanf

		//sscanf(argv[2], "%c", &op)
		mv		a0, s1
		la		a1, char_scan
		addi	a2, sp, 40
		call	sscanf

		//sscanf(argv[3], "%d", &right)
		mv		a0, s2
		la		a1, integer_scan
		addi	a2, sp, 48
		call	sscanf

		//loads each possible operator into a temporary register for comparison to given op
		li		t0, '+'
		li		t1, '-'
		li		t2, 'x'
		li		t3, '/'
		li		t4, '%'
		lb		a0, 40(sp) //loads given op into a0

		//compares given op to every possible op, if none match branches to error
		beq		a0, t0, 1f
		beq		a0, t1, 2f
		beq		a0, t2, 3f
		beq		a0, t3, 4f
		beq		a0, t4, 5f
		j		7f

	//addition
	1:
		lw		a0, 32(sp)
		lw		a1, 48(sp)
		call	addition		
		j		6f
	//subtraction
	2:
		lw		a0, 32(sp)
		lw		a1, 48(sp)
		call	subtract
		j		6f
	//multiplication
	3:
		lw		a0, 32(sp)
		lw		a1, 48(sp)
		call	multiply
		j		6f
	//division
	4:
		lw		a0, 32(sp)
		lw		a1, 48(sp)
		call	divide
		j		6f
	//modulo
	5:
		lw		a0, 32(sp)
		lw		a1, 48(sp)
		call	modulo
		j		6f
	//successful output after arithmetic is performed
	6:
		//printf("%d %c %d = %d\n", left, op, right, result)
		sd		a0, 56(sp) //store result of function on stack
		la		a0, output 
		lw		a1, 32(sp) //left
		lb		a2, 40(sp) //op
		lw		a3, 48(sp) //right
		lw		a4, 56(sp) //result
		call	printf
		j		exit
	//error for unknown operator
	7:
		//printf("Unknown operator '%c'\n", op)
		la		a0, not_op
		lb		a1, 40(sp) //op
		call	printf
		j		exit		
	//error for not enough arguments
	not_enough_arguments:
		//outputs error and exits program
		la		a0, not_enough
		call	printf
		ld		ra, 0(sp)
		ret
	//error for too many arguments
	too_many_arguments:
		//outputs error and exits program
		la		a0, too_many
		call printf
		ld		ra, 0(sp)
		ret
	//successful exit
	exit: 
		//restores save registers and exits program
		ld		ra, 0(sp)
		ld		s0, 8(sp)
		ld		s1, 16(sp)
		ld		s2, 24(sp)
		ret

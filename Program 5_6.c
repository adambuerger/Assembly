//Adam Buerger
//CSC 362 Programs 5
//Program 5 uses assembly to test all numbers 2-100 to see if n*6+1 and n*6-1 are prime numbers, and prints all values of n where both results are prime
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void main() {
	int n = 2;							//int variable used to store the current value being checked
	int nMinus;							//int variable used to store n*6-1
	int nPlus;							//int variable used to store n*6+1
	int primeChecker;					//int variable used to check all numbers between 2 and nMinus/2 and nPlus/2 in order to determine if either nMinus or nPlus is prime
	int isPrime;						//"boolean" variable used to flag an if statment at the end of the outer for loop to print n if both nMinus and nPlus are prime
	int six = 6, two = 2;				//constants used 
	int limit;							//int variable to store nPlus/2 for the inner loop condition since it is the largest number that could potentially divide nPlus
/*
No number is evenly divisible by any number greater than itself divided by two so you only need to check all numbers 2 through n/2.
No number that is checked is even since all instances of n are multiplied by an even number and then 1 is added or subtracted so there's
no real reason to check 2 or n/2 but I'd rather run the extra two checks just to be sure everything is running the way it should.
*/
	__asm {
start:	mov isPrime, 1						//isPrime = 1, we will come back to this line after every pass through the loop
		mov primeChecker, 2					//primeChecker always starts a 2. If we started at 1 then all numbers would be flagged as non-prime
		mov eax, n							//move n into the eax so arithmetic operations can be performed on it
		mul six								//n*6
		add eax, 1							//n*6+1
		mov nPlus, eax						//nPlus = n*6+1
		mov edx, 0							//clear edx for division
		div two								//(n*6+1)/2
		mov limit, eax						//limit = (n*6+1)/2, this is so we can set this value as the top limit of the loop
		mov eax, nPlus						//move nPlus back into the eax so we can find the other value that we need to check for primeness
		sub eax, 2							//nPlus - 2 
		mov nMinus, eax						//nMinus = nPlus - 2
		top:	mov eax, limit				//move limit to the eax so we can check primeChecker against it for the loop
				cmp primeChecker, eax		//if primeChecker > limit
					jg bottom				//jump to the end of the loop
					mov eax, nPlus			//move nPlus into the eax for future division
					mov edx, 0				//clear the edx to prepare for division
					div primeChecker		//divide nPlus by primeChecker in order to check the remainder
					cmp edx, 0				//if nPlus % primeChecker == 0
						je fwd1				//go to the place that changes isPrime
			back1:	mov eax, nMinus			//now we need to check if nMinus is prime
					mov edx, 0				//prepare for division
					div primeChecker		//nMinus / primeChecker
					cmp edx, 0				//if nMinus % primeChecker == 0
						je fwd2				//go to the other place that changes isPrime
			back2:	mov eax, primeChecker	//primeChecker = primeChecker
					add eax, 1				//primeChecker + 1
						mov primeChecker, eax	//primeChecker  = primeChecker + 1
					jmp top					//jump back to the top of the loop and see if we need to run through it again
//I'm gonna be honest, I have literally no clue why this works but putting the change immediately after the cmp command doesn't.
//All I know is that this functions the way this is supposed to function.
			fwd1:	mov isPrime, 0			//if nPlus % primeChecker == 0, set isPrime to 0 since both nPlus and nMinus have to be prime to output n
					jmp back1				//go back to check nMinus
			fwd2:	mov isPrime, 0			//if nMinus % primeChecker == 0, set isPrime to 0 since both nPlus and nMinus have to be prime to output n
					jmp back2				//go back to incriment primeChecker
		bottom:	cmp isPrime, 0				//if isPrime == 0
					je skip					//skip the print statment
	}
	printf("%d ", n);
	__asm {
		//now we incriment n and check to see if we need to run the loop again
		skip:	mov eax, n					//n = n
				add eax, 1					//n + 1
				mov n, eax					//n = n + 1
				cmp n, 101					//if n != 101
					jne start				//jump to the start of the program
	}
	scanf("%d", n);
}
//Program 5 Output: 2 3 5 7 10 12 17 18 23 25 30 32 33 38 40 45 47 52 58 70 72 77 87 95 100
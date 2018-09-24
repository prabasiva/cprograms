/*

Purpose: Prime number generator.
Author : @prabasiva, praba@umich.edu, mail@prabasiva.com
Testing: primitive

Opportunity: Improve the efficieny for large prime number.



*/
#define isEven(_input) !(_input%2)
#define FALSE 0
#define TRUE 1
int isPrime(int);
void printPrime(int);
void printPrimeUpTo(int);
int digitSum(int);
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
printPrime(99999999);
printPrimeUpTo(1000);
return 1;
}

int isDiv3(_input)
{
	return !(digitSum(_input)%3);

}

int digitSum(_input)
{

int quo, rem;
int sum = 0;	
	while (_input > 0)
	{
	quo = _input / 10;
	rem = _input % 10;
	sum = sum+rem;
	_input = quo;
	}

return sum;

}

void printPrimeUpTo(_input)
{
int i;
for(i=1;i<_input;i++)
{

if (isPrime(i))
	printf("%d\t",i);

}
printf("\n");

return;
}

void printPrime(int _input)
{

int count = 0;
int number = -1;

	while (TRUE)
	{
		if (isPrime(number+=2))
		{
			count++;
			printf("%d\t",number);
			if (_input  < count)
				break;

		}
	}
	printf("\n");
}

		
int isPrime(int _input)
{

int midPoint,i;

	if (_input == 2) 
		return TRUE;
	if (isEven(_input))
		return FALSE;
	if (isDiv3(_input))
		return FALSE;
	else
	{
		midPoint = sqrt(_input);
		for (i = 5 ; i <= midPoint; i+=2)
		{
			if (!(_input%i))
				return FALSE;
		}
	}

		return TRUE;
}

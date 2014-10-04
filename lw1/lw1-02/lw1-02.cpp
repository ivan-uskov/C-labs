#include "stdafx.h"

int digitSum(int num)
{
	int sum = 0;
	while (num > 0)
	{
		sum += num % 10;
		num = num / 10;
	}
	return sum;
}

void printLw12()
{
	const int UPPER_BOUND = 1000;
	const int LOWWER_BOUND = 1;

	for (int i = LOWWER_BOUND; i <= UPPER_BOUND; i++)
	{
		if (i % digitSum(i) == 0)
		{
			printf("%4d\n", i);
		}
	}
}

int main(int argc, char* argv[])
{
	printLw12();
	return 0;
}
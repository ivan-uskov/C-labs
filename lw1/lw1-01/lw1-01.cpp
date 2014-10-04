#include "stdafx.h"

void printEvenInHandred()
{
	const int LOWER_BOUND = 1;
	const int UPPER_BOUND = 100;
	const int STEP = 2;

	for (int i = UPPER_BOUND / STEP * STEP; i > LOWER_BOUND; i -= STEP)
	{
		printf("%3d", i);
		if (i - LOWER_BOUND >= STEP)
		{
			printf(", ");
		}
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	printEvenInHandred();
	return 0;
}
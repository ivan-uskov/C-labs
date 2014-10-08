#include "stdafx.h"

const int LOWER_BOUND = 1;
const int DEFAULT_UPPER_BOUND = 1000;

int SumDigits(int i)
{
    int sum = 0;

    while (i > 0)
    {
        sum += i % 10;
        i /= 10;
    }

    return sum;
}

void PrintSpecialNumbers(int upperBound)
{
    for (int i = LOWER_BOUND; i <= upperBound; i++)
    {
        if (i % SumDigits(i) == 0)
        {
            printf("%4d ", i);
        }
    }
    printf("\n");
}

int StringToInt(const char * str, bool & err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}


int main(int argc, char* argv[])
{
    int upperBound;
    int userUpperBound = 0; //user can set by first command line parameter
    bool errors;

    if (argc > 1)
    {
        userUpperBound = StringToInt(argv[1], errors);
    }

    if (userUpperBound > LOWER_BOUND && !errors)
    {
        upperBound = userUpperBound;
    }
    else
    {
        upperBound = DEFAULT_UPPER_BOUND;
    }

    PrintSpecialNumbers(upperBound);
    return 0;
}
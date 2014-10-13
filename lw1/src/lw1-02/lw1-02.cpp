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
    int upperBound = DEFAULT_UPPER_BOUND;
    int userUpperBound = 0; //user can set by first command line parameter

    if (argc > 1)
    {
        bool errors;
        userUpperBound = StringToInt(argv[1], errors);
        
        if (errors)
        {
            printf("Invalid argument!");
            return 1;
        }

        if (userUpperBound > LOWER_BOUND)
        {
            upperBound = userUpperBound;
        }
    }

    PrintSpecialNumbers(upperBound);
    return 0;
}
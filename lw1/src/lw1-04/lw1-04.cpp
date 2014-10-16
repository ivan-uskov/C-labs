#include "stdafx.h"
#include <climits>

typedef long int ArgumentType;

const ArgumentType MIN_N = 2;
const ArgumentType FIRST_FIB_NUM = 1;
const ArgumentType SECOND_FIB_NUM = 1;

const int ELEMENTS_IN_ROW = 5;

bool CheckCanPrintSequence(ArgumentType n)
{
    return (n > MIN_N && n <= INT_MAX); 
}

bool CheckCanAddup(const ArgumentType maxVal, ArgumentType x, ArgumentType y)
{
    return ( (maxVal - x) >= y );
}

ArgumentType StringToInt(const char * str, bool & err)
{
    char * pLastChar = NULL;
    ArgumentType param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}

void PrintSequence(const ArgumentType n)
{
    ArgumentType untilLast = FIRST_FIB_NUM;
    ArgumentType last = SECOND_FIB_NUM;
    ArgumentType curr;

    int newLineCounter = ELEMENTS_IN_ROW - 2;
    printf("%15d, ", untilLast);
    printf("%15d, ", last);
    bool canAddup = CheckCanAddup(n, untilLast, last);

    while (canAddup)
    {
        curr = untilLast + last;
        untilLast = last;
        last = curr;

        printf("%15d", curr);

        canAddup = CheckCanAddup(n, untilLast, last);
        if (canAddup)
        {
            printf(", ");
        }
        else
        {
            printf("\n");
        }

        newLineCounter--;
        if (newLineCounter == 0)
        {
            newLineCounter = ELEMENTS_IN_ROW;
            printf("\n");
        }
    }
}

int main(int argc, char* argv[])
{ 
    if (argc <= 1)
    {
        printf("\nPlease enter max number: 2 <= N <= %d \n", INT_MAX);
        return 1;
    }

    bool err;
    const ArgumentType n = StringToInt(argv[1], err);

    if (err)
    {
        printf("\nInvalid argument! \nUsage: [MAX_INTEGER_NUMBER]\n");
        return 1;
    }

    bool canPrintSequence = CheckCanPrintSequence(n);
    if (canPrintSequence)
    {
        PrintSequence(n);
    }
    else
    {
        printf("\nPlease enter max number: 2 <= N <= %d \n", INT_MAX);
        return 1;
    }
    printf("\n");
    return 0;
}
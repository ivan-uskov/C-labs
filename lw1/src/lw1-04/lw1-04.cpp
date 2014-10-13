#include "stdafx.h"
#include <cfloat>

const double MIN_N = 2;
const double FIRST_FIB_NUM = 0;
const double SECOND_FIB_NUM = 1;

const int ERROR_TOO_BIG_INPUT_VALUE = 0;
const int SUCCESS = 1;

const int ELEMENTS_IN_ROW = 5;

bool CheckCanPrintSequence(const double n)
{
    return (n > MIN_N && ((double)((int)n) == n));
}

bool CheckCanAddup(double x, double y)
{
    return ( (DBL_MAX - x) > y );
}

int PrintSequence(const double n)
{
    double untilLast = FIRST_FIB_NUM;
    double last = SECOND_FIB_NUM;
    double curr;

    int newLineCounter = ELEMENTS_IN_ROW;

    for (double i = MIN_N; i <= n; i++)
    {
        if (!CheckCanAddup(untilLast, last))
        {
            return ERROR_TOO_BIG_INPUT_VALUE;
        }

        curr = untilLast + last;
        untilLast = last;
        last = curr;

        printf("%15.0f ", curr);
        newLineCounter--;

        if (newLineCounter == 0)
        {
            newLineCounter = ELEMENTS_IN_ROW;
            printf("\n");
        }
    }
    return SUCCESS;
}

int main(int argc, char* argv[])
{ 
    if (argc <= 1)
    {
        printf("\nPlease enter max number - N >= 2\n");
        return 1;
    }

    const double n = strtod(argv[1], NULL);

    bool canPrintSequence = CheckCanPrintSequence(n);
    if (canPrintSequence)
    {
        int code = PrintSequence(n);
        if (code == ERROR_TOO_BIG_INPUT_VALUE)
        {
            printf("\nSorry, too big input max number\n");
        }
    }
    else
    {
        printf("\nInvalid argument, its sholud be natural number N >= 2\n");
        return 1;
    }
    printf("\n");
    return 0;
}
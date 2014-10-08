#include "stdafx.h"

const char PLUS = '+';
const char MINUS = '-';
const char DIVISION = '/';
const char MULTIPLICATION = '*';

enum parseFlag
{
    Number,
    Operator
};

enum evalOperator
{
    Plus,
    Minus,
    Division,
    Multiplication,
    ParseError
};

int StringToInt(const char * str, bool & err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}

double StringToDouble(const char * str, bool & err)
{
    err = false;
    double d1 = strtod(str, NULL);
    if (d1 == 0)
    {
        StringToInt(str, err);
    }
    return d1;
}

evalOperator parseOperator(const char * str, bool & err)
{
    evalOperator parsedOperator = ParseError;
    err = false;
    switch (*str)
    {
        case PLUS:
            parsedOperator = Plus;
            break;
        case MINUS:
            parsedOperator = Minus;
            break;
        case DIVISION:
            parsedOperator = Division;
            break;
        case MULTIPLICATION:
            parsedOperator = Multiplication;
            break;
    }

    err = (parsedOperator == ParseError);
    return parsedOperator;
}

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        printf("Program calculates sum of its command line arguments.\n");
        return 0;
    }

    int result = 0;
    parseFlag flag = Number;

    for (int i = 1; i < argc; i++)
    {
        bool err;

        if (err)
        {
            printf("Argument erro in %d argument", i);
            return 1;
        }
    }

    return 0;
}

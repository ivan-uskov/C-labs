#include "stdafx.h"

const int PARAMS_COUNT = 3;

struct EquationArguments
{
    int a;
    int b;
    int c;
};

int StringToInt(const char * str, bool & err)
{
    char * pLastChar = NULL;
    int param = strtol(str, &pLastChar, 10);
    err = ((*str == '\0') || (*pLastChar != '\0'));
    return param;
}

bool СheckFirstArgument(int a)
{
    return a > 0;
}

bool InitEquationArgumentsFromArgv(char *argv[], EquationArguments *arguments)
{
    bool err;
    arguments->a = StringToInt(argv[1], err);
    if (err || !СheckFirstArgument(arguments->a))
    {
        return false;
    }

    arguments->b = StringToInt(argv[2], err);
    if (err)
    {
        return false;
    }

    arguments->c = StringToInt(argv[3], err);
    if (err)
    {
        return false;
    }
    return true;
}

void ProcessTwoRoots(EquationArguments *arguments, double descrimenant)
{
    double root1 = (-arguments->b + sqrt(descrimenant)) / 2 * arguments->a;
    double root2 = (-arguments->b - sqrt(descrimenant)) / 2 * arguments->a;
    printf("Root1: %.4f\n", root1);
    printf("Root2: %.4f\n", root2);
}

void ProcessOneRoot(EquationArguments *arguments)
{
    double root = - arguments->b / 2 * arguments->a;
    printf("Root: %.4f\n", root);
}

void ProcessZeroRoots()
{
    printf("There is no real root.\n");
}

void resolveEquatiton(EquationArguments *arguments)
{
    double descrimenant = pow(arguments->b, 2) - 4 * arguments->a * arguments->c;

    if (descrimenant > 0)
    {
        ProcessTwoRoots(arguments, descrimenant);
    }
    else if (descrimenant == 0)
    {
        ProcessOneRoot(arguments);
    }
    else
    {
        ProcessZeroRoots();
    }
}

int main(int argc, char *argv[])
{
    if (argc <= PARAMS_COUNT)
    {
        printf("Expected arguments: [A] [B] [C]\n");
        return 1;
    }

    EquationArguments *arguments = new EquationArguments;

    if (!InitEquationArgumentsFromArgv(argv, arguments))
    {
        printf("Invalid parameters!\n");
        return 1;
    }

    resolveEquatiton(arguments);

    return 0;
}
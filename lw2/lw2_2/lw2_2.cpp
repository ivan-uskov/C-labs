#include "stdafx.h"

using namespace std;

enum class RootsQuantity
{
    Zero,
    One,
    Two
};

struct EquationArguments
{
    double a;
    double b;
    double c;
};

struct EquationRoots
{
    RootsQuantity count;
    double first = NAN;
    double second = NAN;
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
    if (fabs(d1) < DBL_EPSILON)
    {
        StringToInt(str, err);
    }
    return d1;
}

bool СheckFirstArgument(double a)
{
    return a > 0;
}

bool InitEquationArgumentsFromArgv(char *argv[], EquationArguments &arguments)
{
    bool err;
    arguments.a = StringToDouble(argv[1], err);
    if (err)
    {
        return false;
    }

    arguments.b = StringToDouble(argv[2], err);
    if (err)
    {
        return false;
    }

    arguments.c = StringToDouble(argv[3], err);
    if (err)
    {
        return false;
    }
    return true;
}

void CalcTwoRoots(EquationArguments const& arguments, const double discriminant, EquationRoots & roots)
{
    roots.first = (-arguments.b + sqrt(discriminant)) / (2 * arguments.a);
    roots.second = (-arguments.b - sqrt(discriminant)) / (2 * arguments.a);
    
}

void CalcOneRoot(EquationArguments const& arguments, double & root)
{
    root = (-1) * arguments.b / (2 * arguments.a);
}

bool ResolveEquatiton(EquationArguments const& arguments, EquationRoots &roots)
{
    double discriminant = pow(arguments.b, 2) - 4 * arguments.a * arguments.c;

    if (!СheckFirstArgument(arguments.a))
    {
        return false;
    }

    if (discriminant > 0)
    {
        roots.count = RootsQuantity::Two;
        CalcTwoRoots(arguments, discriminant, roots);
    }
    else if (fabs(discriminant) < DBL_EPSILON)
    {
        roots.count = RootsQuantity::One;
        CalcOneRoot(arguments, roots.first);
    }
    else
    {
        roots.count = RootsQuantity::Zero;
    }
    return true;
}

void PrintEquationRoots(EquationRoots const& roots)
{
    switch (roots.count)
    {
        case RootsQuantity::Zero:
        {
            cout << "There is no real root.\n";
            break;
        }
        case RootsQuantity::One:
        {
            cout << "Root: " << roots.first << "\n";
            break;
        }
        case RootsQuantity::Two:
        {
            cout << "Root1: " << roots.first << "\n";
            cout << "Root2: " << roots.second << "\n";
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    const int PARAMS_COUNT = 3;
    if (argc <= PARAMS_COUNT)
    {
        printf("Expected arguments: [A] [B] [C]\n");
        return 1;
    }

    EquationArguments arguments;

    if (!InitEquationArgumentsFromArgv(argv, arguments))
    {
        printf("Invalid parameters!\n");
        return 1;
    }

    EquationRoots roots;
    if (!ResolveEquatiton(arguments, roots))
    {
        cout << "Invalid parameters! Equation doesn't square!\n";
        return 1;
    }

    PrintEquationRoots(roots);

    return 0;
}
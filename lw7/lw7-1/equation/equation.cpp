#include "stdafx.h"
#include "EquationSolve.h"

using namespace std;

struct Equation3
{
    double a, b, c, d;
};

Equation3 ReadEquation3(istream & in)
{
    Equation3 equation;

    if (!(in >> equation.a >> equation.b >> equation.c >> equation.d))
    {
        throw domain_error("Impossible to parse this coefs!");
    }

    return equation;
}

ostream & operator << (ostream & out, EquationRoots3 const& solution)
{
    out << "Roots: ";
    for (int i = 0; i < solution.numRoots; ++i)
    {
        out << (!DblsEqualy(solution.roots[i], 0) ? solution.roots[i] : 0) << "; ";
    }
    out << endl;

    return out;
}

int main(int argc, char* argv[])
{
    string equationLine;
    cout << "Enter equation coefs, like '1 4 3 -2'" << endl;

    while (!cin.eof())
    {
        getline(cin, equationLine);
        try
        {
            auto equation = ReadEquation3(istringstream(equationLine));
            cout << Solve3(equation.a, equation.b, equation.c, equation.d);
        }
        catch (exception const& e)
        {
            cout << e.what() << endl;
        }
    }

    return 0;
}


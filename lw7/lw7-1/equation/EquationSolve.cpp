#include "stdafx.h"
#include "EquationSolve.h"
#include "Complex.h"

/*
    Solve 3 equation with Viet-Cardano formula
*/

using namespace std;

namespace
{
    double ch(double num)
    {
        return cosh(num);
    }

    double arch(double num)
    {
        return acosh(num);
    }

    double sh(double num)
    {
        return sinh(num);
    }

    double arsh(double num)
    {
        return asinh(num);
    }

    int Sign(double num)
    {
        return !DblsEqualy(num, 0) ? static_cast<int>(num / abs(num)) : 0;
    }

    double Root(double num, unsigned step)
    {
        if (Sign(num) == -1 && (step % 2 == 0))
        {
            throw invalid_argument("Can't get root with positive step from negative number!");
        }

        return Sign(num) * pow(abs(num), 1.0 / step);
    }

    double Get_Q_Coef(double a, double b)
    {
        return (pow(a, 2) - 3 * b) / 9;
    }

    double Get_R_Coef(double a, double b, double c)
    {
        return (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
    }

    double Get_S_Coef(double Q, double R)
    {
        return pow(Q, 3) - pow(R, 2);
    }

    EquationRoots3 GetSolutionWhenSEqualZero(double R, double a)
    {
        EquationRoots3 solution;

        solution.numRoots = 2;
        solution.roots[0] = Root(R, 3) - a / 3;
        solution.roots[1] = -2 * Root(R, 3) - a / 3;

        return solution;
    }

    EquationRoots3 GetSolutionWhenSMoreThanZero(double Q, double R, double a)
    {
        EquationRoots3 solution;

        auto phi = (1.0 / 3) * acos(R / sqrt(pow(Q, 3)));
        solution.numRoots = 3;
        solution.roots[0] = -2 * sqrt(Q) * cos(phi) - a / 3;
        solution.roots[1] = -2 * sqrt(Q) * cos(phi + (2.0 * M_PI) / 3) - a / 3;
        solution.roots[2] = -2 * sqrt(Q) * cos(phi - (2.0 * M_PI) / 3) - a / 3;

        return solution;
    }

    EquationRoots3 GetSolutionWhenSLessThanZero(double Q, double R, double a, double c)
    {
        EquationRoots3 solution;

        solution.numRoots = 1;
        if (DblsEqualy(Q, 0))
        {
            solution.roots[0] = -(Root(c - pow(a, 3) / 27.0, 3) + a / 3);
        }
        else
        {
            function<double(double)> straight = (Q > 0) ? ch : sh;
            function<double(double)> reverse = (Q > 0) ? arch : arsh;

            auto phi = (1.0 / 3) * reverse(abs(R) / sqrt(pow(abs(Q), 3)));
            solution.roots[0] = -2 * Sign(R) * sqrt(abs(Q)) * straight(phi) - a / 3;
        }

        return solution;
    }

    EquationRoots3 GetSolutionOfProvidedEquation3(double a, double b, double c)
    {
        double Q = Get_Q_Coef(a, b);
        double R = Get_R_Coef(a, b, c);
        double S = Get_S_Coef(Q, R);

        EquationRoots3 solution;
        if (DblsEqualy(S, 0))
        {
            solution = GetSolutionWhenSEqualZero(R, a);
        }
        else if (S > 0)
        {
            solution = GetSolutionWhenSMoreThanZero(Q, R, a);
        }
        else
        {
            solution = GetSolutionWhenSLessThanZero(Q, R, a, c);
        }

        return solution;
    }
};

EquationRoots3 Solve3(double a, double b, double c, double d)
{
    if (DblsEqualy(a, 0))
    {
        throw invalid_argument("This equation not cubic!");
    }

    b /= a;
    c /= a;
    d /= a;

    // Now b is a, c is b, d is c
    return GetSolutionOfProvidedEquation3(b, c, d);
}
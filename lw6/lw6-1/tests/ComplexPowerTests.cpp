#include "stdafx.h"
#include "../numbers/Complex.h"

using namespace std;

double Round(double num, int precision)
{
    for (int i = precision; i > 0; --i)
    {
        num *= 10;
    }

    num = std::round(num);

    for (int i = precision; i > 0; --i)
    {
        num /= 10;
    }

    return num;
}

bool ComplexAreEqual(CComplex const& lhs, CComplex const& rhs, int precision = 3)
{
    return Round(lhs.Re(), precision) == Round(rhs.Re(), precision) &&
        Round(lhs.Im(), precision) == Round(rhs.Im(), precision);
}

BOOST_AUTO_TEST_SUITE(CComplexPowerOperatorTests)

BOOST_AUTO_TEST_CASE(CheckPowerOperatorWorkCorrectly)
{
    // Positive steps
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (4)), CComplex(-527, -336)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (2.5)), CComplex(-2.121, -55.861)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (0.5)), CComplex(2.121, -0.707)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (0.25)), CComplex(1.476, -0.240)));

    // Nagative steps
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (-4)), CComplex(-0.001, 0.001)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (-2.5)), CComplex(-0.001, 0.018)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (-0.5)), CComplex(0.424, 0.141)));
    BOOST_CHECK(ComplexAreEqual((CComplex(4, -3) ^ (-0.25)), CComplex(0.660, 0.107)));
}

BOOST_AUTO_TEST_SUITE_END()
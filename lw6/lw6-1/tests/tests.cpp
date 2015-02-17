#include "stdafx.h"
#include "../numbers/Complex.h"

using namespace std;

string const GetComplexAsString(CComplex const& num)
{
    ostringstream strm;
    strm << num;
    return strm.str();
}

CComplex const GetComplexFromString(string const& str)
{
    CComplex num;
    istringstream(str) >> num;
    return num;
}

bool NewComplexCorrect(double re, double im)
{
    bool isCorrect = true;
    CComplex num(re, im);

    BOOST_CHECK(isCorrect = isCorrect && DblsEqualy(num.Re(), re));
    BOOST_CHECK(isCorrect = isCorrect && DblsEqualy(num.Im(), im));
    BOOST_CHECK(isCorrect = isCorrect && DblsEqualy(num.GetMagnitude(), sqrt(pow(re, 2) + pow(im, 2))));
    BOOST_CHECK(isCorrect = isCorrect && DblsEqualy(num.GetArgument(), (DblsEqualy(re, 0) ? (M_PI / 2) : atan(im / re))));

    return isCorrect;
}

BOOST_AUTO_TEST_SUITE(CComplexTests)

BOOST_AUTO_TEST_CASE(DefaultComplex)
{
    {
        CComplex num;
        BOOST_CHECK(DblsEqualy(num.Re(), 0));
        BOOST_CHECK(DblsEqualy(num.Im(), 0));
        BOOST_CHECK(DblsEqualy(num.GetMagnitude(), 0));
    }

    CComplex num(1);
    BOOST_CHECK(DblsEqualy(num.Re(), 1));
    BOOST_CHECK(DblsEqualy(num.Im(), 0));
    BOOST_CHECK(DblsEqualy(num.GetMagnitude(), 1));
    BOOST_CHECK(DblsEqualy(num.GetArgument(), 0));
}

// Числа с отрицательными и положительными частями
BOOST_AUTO_TEST_CASE(NewNumberInQuaters)
{
    BOOST_CHECK(NewComplexCorrect(1.8, 2.5)); // First Quater
    BOOST_CHECK(NewComplexCorrect(-1.8, 2.5)); //Second Quater
    BOOST_CHECK(NewComplexCorrect(1.8, -2.5)); //Fourth Quater
    BOOST_CHECK(NewComplexCorrect(-1.8, -2.5)); //Third Quater
}

// Числа находяться на осях
BOOST_AUTO_TEST_CASE(NewNumberInAxis)
{
    BOOST_CHECK(NewComplexCorrect(1.8, 0));
    BOOST_CHECK(NewComplexCorrect(0, 2.5));
    BOOST_CHECK(NewComplexCorrect(0, -2.5));
    BOOST_CHECK(NewComplexCorrect(-1.8, 0));
}

// Сравнение комплексных чисел
BOOST_AUTO_TEST_CASE(ComparisonTest)
{
    BOOST_CHECK(CComplex(1, 8) == CComplex(1, 8));
    BOOST_CHECK(CComplex(8, 1) == CComplex(8, 1));
    BOOST_CHECK(CComplex(-1, 8) == CComplex(-1, 8));
    BOOST_CHECK(CComplex(-8, 1) == CComplex(-8, 1));
    BOOST_CHECK(CComplex(-8, -1) == CComplex(-8, -1));
    BOOST_CHECK(CComplex(8, -1) == CComplex(8, -1));
    BOOST_CHECK(CComplex(1, -8) == CComplex(1, -8));

    BOOST_CHECK(2 == CComplex(2));

    BOOST_CHECK(CComplex(8, 1) != CComplex(1, 8));
    BOOST_CHECK(CComplex(1, 8) != CComplex(8, 1));
    BOOST_CHECK(CComplex(8, -1) != CComplex(-1, 8));
    BOOST_CHECK(CComplex(1, -8) != CComplex(-8, 1));
    BOOST_CHECK(CComplex(-1, -8) != CComplex(-8, -1));
    BOOST_CHECK(CComplex(-1, 8) != CComplex(8, -1));
    BOOST_CHECK(CComplex(-8, 1) != CComplex(1, -8));
    BOOST_CHECK(2 != CComplex(1, -8));
}

// Сложение комплексных чисел
BOOST_AUTO_TEST_CASE(AdditionTest)
{
    BOOST_CHECK((CComplex(1, 8) + CComplex(2, 7)) == CComplex(3, 15));
    BOOST_CHECK((CComplex(1, -8) + CComplex(2, 7)) == CComplex(3, -1));
    BOOST_CHECK((CComplex(-1, 8) + CComplex(2, 7)) == CComplex(1, 15));
    BOOST_CHECK((CComplex(-1, -8) + CComplex(2, 7)) == CComplex(1, -1));

    BOOST_CHECK((4 + CComplex(2, 7)) == CComplex(6, 7));

    CComplex num;
    BOOST_CHECK(&(num + 1) != &num);

    BOOST_CHECK((CComplex(1, 8) += CComplex(2, 7)) == CComplex(3, 15));
    BOOST_CHECK((CComplex(1, -8) += CComplex(2, 7)) == CComplex(3, -1));
    BOOST_CHECK((CComplex(-1, 8) += CComplex(2, 7)) == CComplex(1, 15));
    BOOST_CHECK((CComplex(-1, -8) += CComplex(2, 7)) == CComplex(1, -1));

    CComplex num1;
    auto addr = &num1;
    BOOST_CHECK(&(num1 += 1) == &num1);
}

// Вычитание комплексных чисел
BOOST_AUTO_TEST_CASE(SubtractionTest)
{
    BOOST_CHECK((CComplex(1, 8) - CComplex(2, 7)) == CComplex(-1, 1));
    BOOST_CHECK((CComplex(1, -8) - CComplex(2, 7)) == CComplex(-1, -15));
    BOOST_CHECK((CComplex(-1, 8) - CComplex(2, 7)) == CComplex(-3, 1));
    BOOST_CHECK((CComplex(-1, -8) - CComplex(2, 7)) == CComplex(-3, -15));

    BOOST_CHECK((4 - CComplex(2, 7)) == CComplex(2, -7));

    CComplex num;
    BOOST_CHECK(&(num - 1) != &num);

    BOOST_CHECK((CComplex(1, 8) -= CComplex(2, 7)) == CComplex(-1, 1));
    BOOST_CHECK((CComplex(1, -8) -= CComplex(2, 7)) == CComplex(-1, -15));
    BOOST_CHECK((CComplex(-1, 8) -= CComplex(2, 7)) == CComplex(-3, 1));
    BOOST_CHECK((CComplex(-1, -8) -= CComplex(2, 7)) == CComplex(-3, -15));

    CComplex num1;
    auto addr = &num1;
    BOOST_CHECK(&(num1 -= 1) == &num1);
}

// Умножение комплексных чисел
BOOST_AUTO_TEST_CASE(MultiplicationTest)
{
    BOOST_CHECK((CComplex(1, 8) * CComplex(2, 7)) == CComplex(-54, 23));
    BOOST_CHECK((CComplex(1, -8) * CComplex(2, 7)) == CComplex(58, -9));
    BOOST_CHECK((CComplex(-1, 8) * CComplex(2, 7)) == CComplex(-58, 9));
    BOOST_CHECK((CComplex(-1, -8) * CComplex(2, 7)) == CComplex(54, -23));

    BOOST_CHECK((4 * CComplex(2, 7)) == CComplex(8, 28));

    CComplex num;
    BOOST_CHECK(&(num - 1) != &num);

    BOOST_CHECK((CComplex(1, 8) *= CComplex(2, 7)) == CComplex(-54, 23));
    BOOST_CHECK((CComplex(1, -8) *= CComplex(2, 7)) == CComplex(58, -9));
    BOOST_CHECK((CComplex(-1, 8) *= CComplex(2, 7)) == CComplex(-58, 9));
    BOOST_CHECK((CComplex(-1, -8) *= CComplex(2, 7)) == CComplex(54, -23));

    CComplex num1;
    auto addr = &num1;
    BOOST_CHECK(&(num1 *= 1) == &num1);
}

// Деление комплексных чисел
BOOST_AUTO_TEST_CASE(DivisionTest)
{
    BOOST_CHECK((CComplex(1, 8) / CComplex(2, 7)) == CComplex(58.0 / 53, 9.0 / 53));
    BOOST_CHECK((CComplex(1, -8) / CComplex(2, 7)) == CComplex(-54.0 / 53, -23.0 / 53));
    BOOST_CHECK((CComplex(-1, 8) / CComplex(2, 7)) == CComplex(54.0 / 53, 23.0 / 53));
    BOOST_CHECK((CComplex(-1, -8) / CComplex(2, 7)) == CComplex(-58.0 / 53, -9.0 / 53));

    BOOST_CHECK((4 / CComplex(2, 7)) == CComplex(8.0 / 53, -28.0 / 53));

    CComplex num;
    BOOST_CHECK(&(num / 1) != &num);

    BOOST_CHECK((CComplex(1, 8) /= CComplex(2, 7)) == CComplex(58.0 / 53, 9.0 / 53));
    BOOST_CHECK((CComplex(1, -8) /= CComplex(2, 7)) == CComplex(-54.0 / 53, -23.0 / 53));
    BOOST_CHECK((CComplex(-1, 8) /= CComplex(2, 7)) == CComplex(54.0 / 53, 23.0 / 53));
    BOOST_CHECK((CComplex(-1, -8) /= CComplex(2, 7)) == CComplex(-58.0 / 53, -9.0 / 53));

    CComplex num1;
    auto addr = &num1;
    BOOST_CHECK(&(num1 /= 1) == &num1);
}

// Вывод в поток
BOOST_AUTO_TEST_CASE(OStreamOperatorTest)
{
    BOOST_CHECK(GetComplexAsString(CComplex(4, 3)) == "+4+3i");
    BOOST_CHECK(GetComplexAsString(CComplex(-4, 3)) == "-4+3i");
    BOOST_CHECK(GetComplexAsString(CComplex(4, -3)) == "+4-3i");
    BOOST_CHECK(GetComplexAsString(CComplex(-4, -3)) == "-4-3i");

    BOOST_CHECK(GetComplexAsString(CComplex(4.2, 3.4)) == "+4.2+3.4i");
    BOOST_CHECK(GetComplexAsString(CComplex(4.2)) == "+4.2+0i");
    BOOST_CHECK(GetComplexAsString(CComplex(0, 4.2)) == "+0+4.2i");
}

// Чтение из потока
BOOST_AUTO_TEST_CASE(IStreamOperatorTest)
{
    BOOST_CHECK(GetComplexFromString("+4+3i") == CComplex(4, 3));
    BOOST_CHECK(GetComplexFromString("-4+3i") == CComplex(-4, 3));
    BOOST_CHECK(GetComplexFromString("+4-3i") == CComplex(4, -3));
    BOOST_CHECK(GetComplexFromString("-4-3i") == CComplex(-4, -3));

    BOOST_CHECK(GetComplexFromString("+4.2+3.4i") == CComplex(4.2, 3.4));
    BOOST_CHECK(GetComplexFromString("+4.2+0i") == CComplex(4.2));
    BOOST_CHECK(GetComplexFromString("+0+4.2i") == CComplex(0, 4.2));
}

BOOST_AUTO_TEST_SUITE_END()
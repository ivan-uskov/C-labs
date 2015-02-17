#pragma once

class CComplex
{
public:

    // инициализация комплексного числа значениями действительной и мнимой частей
    CComplex(double real = 0, double image = 0);

    // возвращает действительную часть комплексного числа
    double Re()const;
    // возвращает мнимую часть комплексного числа
    double Im()const;

    // возвращает модуль комплексного числа
    double GetMagnitude()const;
    // возвращает аргумент комплексного числа
    double GetArgument()const;

    CComplex & operator += (CComplex const& rhs);
    CComplex & operator -= (CComplex const& rhs);

    CComplex & operator *= (CComplex const& rhs);
    CComplex & operator /= (CComplex const& rhs);

    friend std::ostream & operator << (std::ostream & out, CComplex const& num);
    friend std::istream & operator >> (std::istream & in, CComplex & num);

private:
    void Assign(double real, double image);

private:
    double m_real, m_image;
};

bool operator == (CComplex const& lhs, CComplex const& rhs);
bool operator != (CComplex const& lhs, CComplex const& rhs);

CComplex const operator + (CComplex lhs, CComplex const& rhs);
CComplex const operator - (CComplex lhs, CComplex const& rhs);

CComplex const operator * (CComplex lhs, CComplex const& rhs);
CComplex const operator / (CComplex lhs, CComplex const& rhs);

std::ostream & operator << (std::ostream & out, CComplex const& num);
std::istream & operator >> (std::istream & in, CComplex & num);
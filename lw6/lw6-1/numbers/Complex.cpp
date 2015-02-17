#include "stdafx.h"
#include "Complex.h"

using namespace std;

CComplex::CComplex(double real, double image)
    : m_real(real)
    , m_image(image)
{
}

// возвращает действительную часть комплексного числа
double CComplex::Re()const
{
    return m_real;
}

// возвращает мнимую часть комплексного числа
double CComplex::Im()const
{
    return m_image;
}

double CComplex::GetMagnitude()const
{
    return sqrt(pow(m_real, 2) + pow(m_image, 2));
}

double CComplex::GetArgument()const
{
    if (DblsEqualy(m_real, 0))
    {
        return M_PI / 2;
    }

    return atan(m_image / m_real);
}

void CComplex::Assign(double real, double image)
{
    m_real = real;
    m_image = image;
}

bool operator == (CComplex const& lhs, CComplex const& rhs)
{
    return DblsEqualy(lhs.Im(), rhs.Im()) && DblsEqualy(lhs.Re(), rhs.Re());
}

bool operator != (CComplex const& lhs, CComplex const& rhs)
{
    return !(lhs == rhs);
}

CComplex & CComplex::operator += (CComplex const& rhs)
{
    Assign(m_real + rhs.m_real, m_image + rhs.m_image);

    return *this;
}

CComplex const operator + (CComplex lhs, CComplex const& rhs)
{
    return lhs += rhs;
}

CComplex & CComplex::operator -= (CComplex const& rhs)
{
    Assign(m_real - rhs.m_real, m_image - rhs.m_image);

    return *this;
}

CComplex const operator - (CComplex lhs, CComplex const& rhs)
{
    return lhs -= rhs;
}

CComplex & CComplex::operator *= (CComplex const& rhs)
{
    Assign(m_real * rhs.m_real - m_image * rhs.m_image, 
        m_image * rhs.m_real + m_real * rhs.m_image);

    return *this;
}

CComplex const operator * (CComplex lhs, CComplex const& rhs)
{
    return lhs *= rhs;
}

CComplex & CComplex::operator /= (CComplex const& rhs)
{
    if (rhs == 0)
    {
        throw invalid_argument("Division by zero!");
    }

    auto denominator = pow(rhs.m_real, 2) + pow(rhs.m_image, 2);
    Assign((m_real * rhs.m_real + m_image * rhs.m_image) / denominator,
        (m_image * rhs.m_real - m_real * rhs.m_image) / denominator);

    return *this;
}

CComplex const operator / (CComplex lhs, CComplex const& rhs)
{
    return lhs /= rhs;
}

std::ostream & operator << (std::ostream & out, CComplex const& num)
{
    if (num.m_real >= 0 || DblsEqualy(num.m_real, 0))
    {
        out << "+";
    }
    out << num.m_real;

    if (num.m_image > 0 || DblsEqualy(num.m_image, 0))
    {
        out << "+";
    }
    out << num.m_image << "i";

    return out;
}

std::istream & operator >> (std::istream & in, CComplex & num)
{
    auto pos = in.tellg();

    char imageChar = '\0';
    double re, im;

    if (in >> re >> im >> imageChar && imageChar == 'i')
    {
        num.Assign(re, im);
    }
    else
    {
        in.seekg(pos);
        in.setstate(std::ios_base::failbit | in.rdstate());
    }

    return in;
}
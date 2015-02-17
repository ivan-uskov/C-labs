#pragma once

class CComplex
{
public:

    // ������������� ������������ ����� ���������� �������������� � ������ ������
    CComplex(double real = 0, double image = 0);

    // ���������� �������������� ����� ������������ �����
    double Re()const;
    // ���������� ������ ����� ������������ �����
    double Im()const;

    // ���������� ������ ������������ �����
    double GetMagnitude()const;
    // ���������� �������� ������������ �����
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
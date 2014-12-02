#pragma once


class CTransformer
{
public:
    CTransformer(const double positivesSum);
    ~CTransformer();

    double operator() (double i);

private:
    bool m_isEven;
    const double m_positivesSum;
};


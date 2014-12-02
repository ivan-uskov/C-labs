#include "stdafx.h"
#include "Transformer.h"


CTransformer::CTransformer(const double positivesSum)
    : m_isEven(false)
    , m_positivesSum(positivesSum)
{
}


CTransformer::~CTransformer()
{
}

/* Operators */

double CTransformer::operator() (double i)
{
    auto modified = (m_isEven) ? i - m_positivesSum : i * 2;
    m_isEven = !m_isEven;
    return modified;
}

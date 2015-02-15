#include "stdafx.h"
#include "Cone.h"

CCone::CCone(double radius, double height, double density)
    : CSimplexBodyImpl(density)
    , m_radius(radius)
    , m_height(height)
{
    if (!(m_radius > 0 && m_height > 0))
    {
        throw std::invalid_argument("Can'r create cone with this parameters!");
    }
}

double CCone::GetVolume()const
{
    return (1.0 / 3.0) * M_PI * std::pow(m_radius, 2) * m_height;
}

double CCone::GetRadius()const
{
    return m_radius;
}

double CCone::GetHeight()const
{
    return m_height;
}

std::string CCone::ToString()const
{
    return std::string("-- Cone --\n") + CSimplexBodyImpl::ToString();
}
#include "stdafx.h"
#include "Sphere.h"


CSphere::CSphere(double radius, double density)
    : CSimplexBodyImpl(density)
    , m_radius(radius)
{
    if (!(m_radius > 0))
    {
        throw std::invalid_argument("Sphere must have positive radius");
    }
}

/* public */

double CSphere::GetVolume()const
{
    return (1.0 / 3.0) * M_PI * std::pow(m_radius, 3);
}

double CSphere::GetRadius()const
{
    return m_radius;
}

std::string CSphere::ToString()const
{
    return std::string("-- Sphere --\n") + CSimplexBodyImpl::ToString();
}
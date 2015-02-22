#include "stdafx.h"
#include "Sphere.h"

using namespace std;

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
    ostringstream ostrm;
    ostrm << "-- Sphere --" << endl <<
        "Radius: " << m_radius << endl <<
        CSimplexBodyImpl::ToString();

    return ostrm.str();
}
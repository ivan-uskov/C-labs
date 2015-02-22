#include "stdafx.h"
#include "Cylinder.h"

using namespace std;

CCylinder::CCylinder(double radius, double height, double density)
    : CSimplexBodyImpl(density)
    , m_radius(radius)
    , m_height(height)
{
    if (!(m_radius > 0 && m_height > 0))
    {
        throw std::invalid_argument("Can'r create cone with this parameters!");
    }
}

double CCylinder::GetVolume()const
{
    return M_PI * std::pow(m_radius, 2) * m_height;
}

double CCylinder::GetRadius()const
{
    return m_radius;
}

double CCylinder::GetHeight()const
{
    return m_height;
}

std::string CCylinder::ToString()const
{
    ostringstream ostrm;
    ostrm << "-- Cylinder --" << endl <<
        "Radius: " << m_radius << endl <<
        "Height: " << m_height << endl <<
        CSimplexBodyImpl::ToString();

    return ostrm.str();
}
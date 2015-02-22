#include "stdafx.h"
#include "Parallelepiped.h"

using namespace std;

CParallelepiped::CParallelepiped(double width, double height, double depth, double density)
    : CSimplexBodyImpl(density)
    , m_width(width)
    , m_height(height)
    , m_depth(depth)
{
    if (!(m_width > 0 && m_height > 0 && m_depth > 0))
    {
        throw std::invalid_argument("Can'r create parralelepipe with this parameters!");
    }
}

/* private */

double CParallelepiped::GetVolume()const
{
    return m_width * m_height * m_depth;
}

double CParallelepiped::GetWidth()const
{
    return m_width;
}

double CParallelepiped::GetHeight()const
{
    return m_height;
}

double CParallelepiped::GetDepth()const
{
    return m_depth;
}

std::string CParallelepiped::ToString()const
{
    ostringstream ostrm;
    ostrm << "-- Parallelepiped --" << endl <<
        "Width: " << m_width << endl <<
        "Height: " << m_height << endl <<
        "Depth: " << m_depth << endl <<
        CSimplexBodyImpl::ToString();

    return ostrm.str();
}
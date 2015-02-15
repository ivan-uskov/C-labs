#include "stdafx.h"
#include "SimplexBodyImpl.h"

using namespace std;

CSimplexBodyImpl::CSimplexBodyImpl(double density)
    : m_density(density)
{
    if (!(m_density > 0))
    {
        throw invalid_argument("Density should be more than zero!");
    }
}


CSimplexBodyImpl::~CSimplexBodyImpl()
{
}

/* public */

double CSimplexBodyImpl::GetWeight()const
{
    return GetVolume() * m_density;
}

double CSimplexBodyImpl::GetDensity()const
{
    return m_density;
}

std::string CSimplexBodyImpl::ToString()const
{
    ostringstream strm;
    strm << "Volume: " << GetVolume() << endl <<
        "Density: " << m_density << endl <<
        "Weight: " << GetWeight() << endl;

    return strm.str();

}

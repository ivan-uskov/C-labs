#include "stdafx.h"
#include "Compound.h"

using namespace std;

double CCompound::GetMass()const
{
    return accumulate(m_elements.begin(), m_elements.end(), 0.0, [](double sum, shared_ptr<CBody> const& ptr){
        return sum + ptr->GetMass();
    });
}

double CCompound::GetVolume()const
{
    return accumulate(m_elements.begin(), m_elements.end(), 0.0, [](double sum, shared_ptr<CBody> const& ptr){
        return sum + ptr->GetVolume();
    });
}

double CCompound::GetDensity()const
{
    return GetMass() / GetVolume();
}

string CCompound::ToString()const
{
    ostringstream ostrm;
    ostrm << "-- Compound -- with " << m_elements.size() << " elements:" << endl;
    ostrm << accumulate(m_elements.begin(), m_elements.end(), string(), [](string const& sum, shared_ptr<CBody> const& ptr){
        return sum + ptr->ToString();
    });
    ostrm << "--------------" << endl;

    return ostrm.str();
}
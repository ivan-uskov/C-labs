#pragma once
#include "Body.h"

class CSimplexBodyImpl : public CBody
{
public:

    CSimplexBodyImpl(double density = 1);
    virtual ~CSimplexBodyImpl();

    double GetMass()const override final;
    double GetDensity()const override final;
    std::string ToString()const override;

private:
    double m_density;
};


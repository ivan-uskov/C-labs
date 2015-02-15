#pragma once
#include "SimplexBodyImpl.h"

class CSphere : public CSimplexBodyImpl
{
public:
    CSphere(double radius, double density = 1);
    virtual ~CSphere(){};

    double GetVolume()const override;
    double GetRadius()const;

    std::string ToString()const override final;

private:
    double m_radius;
};


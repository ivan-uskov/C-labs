#pragma once
#include "SimplexBodyImpl.h"

class CCylinder : public CSimplexBodyImpl
{
public:
    CCylinder(double radius, double height, double density = 1);
    virtual ~CCylinder(){};

    double GetVolume()const override;
    double GetRadius()const;
    double GetHeight()const;

    std::string ToString()const override final;

private:
    double m_radius;
    double m_height;
};


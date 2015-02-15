#pragma once
#include "SimplexBodyImpl.h"
#include <vector>

class CCone : public CSimplexBodyImpl
{
public:
    CCone(double radius, double height, double density = 1);
    virtual ~CCone(){};

    double GetVolume()const override;
    double GetRadius()const;
    double GetHeight()const;

    std::string ToString()const override final;

private:
    double m_radius;
    double m_height;
};


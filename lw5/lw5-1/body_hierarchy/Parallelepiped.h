#pragma once
#include "SimplexBodyImpl.h"

class CParallelepiped : public CSimplexBodyImpl
{
public:
    CParallelepiped(double width, double height, double depth, double density = 1);
    virtual ~CParallelepiped(){};

    double GetVolume()const override;
    double GetWidth()const;
    double GetHeight()const;
    double GetDepth()const;

    std::string ToString()const override final;

private:
    double m_width;
    double m_height;
    double m_depth;
};


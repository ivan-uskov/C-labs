#pragma once
#include <string>

class CBody
{
public:

    virtual double GetVolume()const = 0;
    virtual double GetDensity()const = 0;
    virtual double GetWeight()const = 0;
    virtual std::string ToString()const = 0;

    virtual ~CBody(){};
};


#pragma once

class CBody
{

public:

    CBody();
    virtual ~CBody();

    virtual size_t GetVolume()const;
    virtual size_t GetDensity()const;
    virtual size_t GetWeight()const;

protected:
    size_t m_volume;
    size_t m_density;
    size_t m_weight;
};


#pragma once
#include "Body.h"
#include "BodyUtils.h"

class CCompound : public CBody
{
public:

    double GetVolume()const override final;
    double GetDensity()const override final;
    double GetMass()const override final;

    std::string ToString()const override final;

    template <typename T>
    void AddBody(T const& body)
    {
        if (!BodyUtils::IsBody(body))
        {
            throw invalid_argument("You can add only figure hierarchy of bodies!");
        }

        m_elements.push_back(make_shared<T>(body));
    }

private:
    std::vector<std::shared_ptr<CBody>> m_elements;
};


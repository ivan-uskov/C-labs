#pragma once
#include "stdafx.h"
#include "Compound.h"

namespace BodyUtils
{
    bool IsCompound(CBody const& body);

    template <typename T>
    bool IsBody(T const& item)
    {
        return dynamic_cast<CBody const*>(addressof(item)) != nullptr;
    }
};

#include "stdafx.h"
#include "BodyUtils.h"

using namespace std;

namespace BodyUtils
{
    bool IsCompound(CBody const& body)
    {
        return dynamic_cast<CCompound const*>(addressof(body)) != nullptr;
    }
};

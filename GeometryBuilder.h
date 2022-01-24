#pragma once

#include "GeometryTypes.h"

namespace geometry
{
    class GeometryBuilder
    {
    public:
        static Base *BuildObject(Base::GeomType type);

    };
}

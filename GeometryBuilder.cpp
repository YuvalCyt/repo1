#include "GeometryBuilder.h"

namespace geometry
{
    ////////////////////////////////////////////
    /// GeometryBuilder
    ////////////////////////////////////////////
    Base*
    GeometryBuilder::BuildObject(Base::GeomType type)
    {
        Base *object(nullptr);
        switch (type)
        {

        case Base::GeomType::PointType:
        {
            object = new Point();
            break;

        }
        case Base::GeomType::CircleType:
        {
            object = new Circle();
            break;
        }        
        case Base::GeomType::UnspecifiedType:
        default:
            assert(0 && "unhandled type");
            break;
        }

        return object;
    }
}

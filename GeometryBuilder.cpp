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
            //todo: report/assert/throw according to the application's architecture
            break;
        }

        return object;
    }
}

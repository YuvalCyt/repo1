
#include "GeometryTypes.h"
#include "OutArchive.h"
#include "InArchive.h"

namespace geometry
{
    ////////////////////////////////////////////
    /// Base
    ////////////////////////////////////////////

    const std::string Base::s_type(std::string("type"));
    const std::string Base::s_numAttrs(std::string("numAttrs"));

    ////////////////////////////////////////////
    /// Point
    ////////////////////////////////////////////

    const std::string Point::s_xPoint(std::string("point_x"));
    const std::string Point::s_yPoint(std::string("point_y"));

    Point::Point(float x, float y)
        : m_x(x), m_y(y)
    {

    }

    size_t 
    Point::GetNumAttrs() const
    {
        return Base::GetNumAttrs() + 2;
    }

    bool
    Point::Write(archive::OutArchive *outArchive) const
    {
        bool bRes(false);
        if (outArchive)
        {
            bRes = true;
            bRes = outArchive->WriteAttribute(Base::s_type, static_cast<short>(GetGeomType())) && bRes;
            bRes = outArchive->WriteAttribute(Base::s_numAttrs, GetNumAttrs()) && bRes;
            bRes = outArchive->WriteAttribute(s_xPoint, m_x) && bRes;
            bRes = outArchive->WriteAttribute(s_yPoint, m_y) && bRes;
        }

        return bRes;
    }

    bool 
    Point::Read(archive::InArchive *inArchive)
    {
        bool bRes(false);
        if (inArchive)
        {
            size_t numAttrs(0);
            bool bRead(inArchive->ReadAttribute(Base::s_numAttrs, numAttrs));
            if (bRead)
            {
                std::vector<std::string> lines(inArchive->ReadAttributes(numAttrs));
                ReadAttributes(lines);
            }
        }

        return bRes;
    }

    void 
    Point::ReadAttributes(const std::vector<std::string> &attributes)
    {
        for (const std::string &attribute : attributes)
        {
            std::string::size_type sepIdx = attribute.find_first_of(':');
            if (std::string::npos != sepIdx)
            {
                if (0 == attribute.compare(0, sepIdx, s_xPoint.c_str()))
                {
                    std::string xString(attribute.substr(sepIdx + 1));
                    m_x = std::stof(xString);
                }
                else if (0 == attribute.compare(0, sepIdx, s_yPoint.c_str()))
                {
                    std::string yString(attribute.substr(sepIdx + 1));
                    m_y = std::stof(yString);
                }
            }
        }
    }

    ////////////////////////////////////////////
    /// Circle
    ////////////////////////////////////////////

    const std::string Circle::s_radius(std::string("radius"));

    Circle::Circle(float x, float y, int r)
        : Point(x, y)
        , m_radius(r)
    {

    }

    size_t
    Circle::GetNumAttrs() const
    {
        return Point::GetNumAttrs() + 1;
    }

    bool
    Circle::Write(archive::OutArchive *outArchive) const
    {
        bool bRes(false);
        if (outArchive)
        {
            bRes = true;
            bRes = Point::Write(outArchive);
            bRes = outArchive->WriteAttribute(s_radius, m_radius) && bRes;
        }

        return bRes;
    }

    bool
    Circle::Read(archive::InArchive *inArchive)
    {
        bool bRes(false);
        if (inArchive)
        {
            size_t numAttrs(0);
            bool bRead(inArchive->ReadAttribute(Base::s_numAttrs, numAttrs));
            if (bRead)
            {
                std::vector<std::string> lines(inArchive->ReadAttributes(numAttrs));
                ReadAttributes(lines);
                bRes = true;
            }
        }

        return bRes;
    }

    void
    Circle::ReadAttributes(const std::vector<std::string> &attributes)
    {
        Point::ReadAttributes(attributes);
        for (const std::string &attribute : attributes)
        {
            std::string::size_type sepIdx = attribute.find_first_of(':');
            if (std::string::npos != sepIdx)
            {
                if (0 == attribute.compare(0, sepIdx, s_radius.c_str()))
                {
                    std::string radiusString(attribute.substr(sepIdx + 1));
                    m_radius = std::stoi(radiusString);
                }
            }
        }
    }
}

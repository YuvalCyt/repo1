#pragma once

#include <string>
#include <vector>

namespace archive
{
    class OutArchive;
    class InArchive;
}

namespace geometry
{
    class Base
    {
    public:
        /*
        * GeomType, an enum (class for being a strong type) object to specify which type it is.
        * Possible to acquire the type at run time.
        * when adding a new 
        */
        enum class GeomType : short { UnspecifiedType = 0, PointType, CircleType };

        virtual Base::GeomType GetGeomType() const = 0;

        /*
        * GetNumAttrs, an unsigned integer, why do we need this?
        * The reason we need this is for the parsing process & backward compatibility.
        * Say we now have 3 attributes for a circle (2 for points, 1 for radius) and we now want to add another attribute
        * In that case we won't be able to properly parse 'legacy' circles
        * Ideally we can't avoid having this in case we save our data in a specific structure like an XML as we can iterate
        * over the sub elements of the circle regardless of their numbers but I believe this is out of the scope of this assignment.
        */
        virtual size_t GetNumAttrs() const { return 0; }

        virtual bool Write(archive::OutArchive *) const { return false; }
        virtual bool Read(archive::InArchive *) { return false; }
        
        static const std::string s_type;
        static const std::string s_numAttrs;

    protected:

        virtual void ReadAttributes(const std::vector<std::string> &) {}
    };

    class Point : public Base
    {
    public:
        Point() = default;
        Point(float x, float y);

        Base::GeomType GetGeomType() const { return Base::GeomType::PointType; }
        size_t GetNumAttrs() const override;

        bool Write(archive::OutArchive *) const override;
        bool Read(archive::InArchive *) override;

        static const std::string s_xPoint;
        static const std::string s_yPoint;

    protected:
        void ReadAttributes(const std::vector<std::string> &) override;

    private:
        float m_x = 0.0f;
        float m_y = 0.0f;
    };

    class Circle : public Point
    {
    public:
        Circle() = default;
        Circle(float x, float y, int r);
        Base::GeomType GetGeomType() const { return Base::GeomType::CircleType; }
        size_t GetNumAttrs() const override;

        bool Write(archive::OutArchive *) const override;
        bool Read(archive::InArchive *) override;

        static const std::string s_radius;

    protected:
        void ReadAttributes(const std::vector<std::string> &attributes) override;

    private:
        int m_radius = 0;
    };
}




#include "OutArchive.h"
#include "GeometryTypes.h"

namespace archive
{
    ////////////////////////////////////////////
    /// OutArchive
    ////////////////////////////////////////////

    OutArchive::OutArchive(const std::string &fileName)
        : m_fileName(fileName)
    {
        OpenFile();
    }

    OutArchive::~OutArchive()
    {
        CloseFile();
    }

    bool 
    OutArchive::Write(const std::vector<std::shared_ptr<geometry::Base>> &objects)
    {
        bool bRes(true);
        for (const std::shared_ptr<geometry::Base> &object : objects)
        {
            bRes = Write(object) && bRes;
        }
            
        return bRes;
    }

    bool
    OutArchive::Write(const std::shared_ptr<geometry::Base> &object)
    {
        bool bRes(true);
        if (object)
        {
            bRes = object->Write(this);
        }

        return bRes;
    }

    bool
    OutArchive::OpenFile()
    {
        bool bRes(false);
        if (!m_fileName.empty())
        {
            m_ostream.open(m_fileName.c_str());
            if (m_ostream && m_ostream.good())
                bRes = true;
        }

        return bRes;
    }

    bool
    OutArchive::CloseFile()
    {
        bool bRes(false);
        if (m_ostream && m_ostream.is_open())
        {
            m_ostream.close();
            bRes = true;
        }

        return bRes;
    }

}
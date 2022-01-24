#include "InArchive.h"
#include "GeometryTypes.h"
#include "GeometryBuilder.h"

namespace archive
{
    ////////////////////////////////////////////
    /// InArchive
    ////////////////////////////////////////////

    InArchive::InArchive(const std::string &fileName)
        : m_fileName(fileName)
    {
        OpenFile();
    }

    InArchive::~InArchive()
    {
        CloseFile();
    }

    bool 
    InArchive::Read(std::vector<std::shared_ptr<geometry::Base>> &objects)
    {
        bool bRes(false);
        if (m_istream && m_istream.is_open())
        {
            for (std::string line; std::getline(m_istream, line); ) 
            {
                std::string::size_type sepIdx = line.find_first_of(':');
                if (std::string::npos != sepIdx) 
                {
                    if (0 == line.compare(0, sepIdx, geometry::Base::s_type))
                    {
                        std::string typeString(line.substr(sepIdx+1));
                        geometry::Base::GeomType gType(static_cast<geometry::Base::GeomType>(std::stoi(typeString)));
                        std::shared_ptr<geometry::Base> sPtr(geometry::GeometryBuilder::BuildObject(gType));
                        if (sPtr)
                        {
                            sPtr->Read(this);
                            objects.push_back(sPtr);
                        }
                    }
                }
            }
        }

        return bRes;
    }

    std::vector<std::string> 
    InArchive::ReadAttributes(size_t numLines)
    {
        std::vector<std::string> lines;
        lines.reserve(numLines);
        for (size_t idx(0); idx < numLines ;++idx)
        {
            std::string line;
            std::getline(m_istream, line);
            lines.emplace_back(std::move(line));
        }

        return lines;
    }

    bool
    InArchive::OpenFile()
    {
        bool bRes(false);
        if (!m_fileName.empty())
        {
            m_istream.open(m_fileName.c_str());
            if (m_istream && m_istream.good())
                bRes = true;
        }

        return bRes;
    }

    bool
    InArchive::CloseFile()
    {
        bool bRes(false);
        if (m_istream && m_istream.is_open())
        {
            m_istream.close();
        }

        return bRes;
    }

}
#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace geometry
{
    class Base;
}

namespace archive
{
    class OutArchive
    {
    public:
        OutArchive(const std::string &fileName);
        ~OutArchive();

        OutArchive(const OutArchive &) = delete;
        OutArchive(OutArchive &&) = delete;

        bool Write(const std::vector<std::shared_ptr<geometry::Base>> &objects);
        bool Write(const std::shared_ptr<geometry::Base> &object);

        template<typename T>
        bool WriteAttribute(const std::string &attributeName, const T &attributeValue)
        {
            bool bRes(false);
            if (m_ostream)
            {
                m_ostream << attributeName << ":" << attributeValue << std::endl;
                bRes = true;
            }
            
            return bRes;
        }

        bool CloseFile();

    protected:

        bool OpenFile();

        std::string m_fileName;
        std::ofstream m_ostream;
    };
}

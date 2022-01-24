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
    class InArchive
    {
    public:
        InArchive(const std::string &fileName);
        ~InArchive();

        InArchive(const InArchive &) = delete;
        InArchive(InArchive &&) = delete;

        bool Read(std::vector<std::shared_ptr<geometry::Base>> &objects);
        template<typename T>
        bool ReadAttribute(const std::string &attributeName, T &value)
        {
            bool bRes(false);
            if (!m_istream.eof())
            {
                std::streamoff pos = m_istream.tellg();
                std::string readAttributeName;
                std::getline(m_istream, readAttributeName, ':');
                if (readAttributeName == attributeName)
                {
                    m_istream >> value;
                    std::getline(m_istream, readAttributeName);
                    bRes = true;
                }
                else
                {
                    m_istream.seekg(pos);
                }
            }

            return bRes;
        }
        std::vector<std::string> ReadAttributes(size_t numLines);


        bool CloseFile();

    protected:

        bool OpenFile();

        std::string m_fileName;
        std::ifstream m_istream;
    };
}

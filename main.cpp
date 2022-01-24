#include "GeometryTypes.h"
#include "OutArchive.h"
#include "InArchive.h"

#include <memory>

int main()
{
    std::vector<std::shared_ptr<geometry::Base>> objects, loaded_objects;
    objects.reserve(3);

    objects.push_back(std::make_shared<geometry::Point>(1.f, 2.f));
    objects.push_back(std::make_shared<geometry::Point>(50.f, 12.f));
    objects.push_back(std::make_shared<geometry::Circle>(0.f, 0.f, 10));

    const std::string fileName("c://out.txt");

    archive::OutArchive write_archive(fileName.c_str());
    write_archive.Write(objects);
    write_archive.CloseFile();

    archive::InArchive read_archive(fileName.c_str());
    read_archive.Read(loaded_objects);
    read_archive.CloseFile();

    return 0;
}


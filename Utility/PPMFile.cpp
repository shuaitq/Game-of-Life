#include "PPMFile.h"

#include <fstream>
#include <stdexcept>

void PPMFile::save(const std::string &path, const int &width, const int &height, const std::vector<bool> &pixel)
{
    std::ofstream out(path);

    if(!out.is_open())
    {
        std::string error("Can't open file: ");
        error += path;
        throw std::runtime_error(error);
    }
    
    out << "P3" << std::endl << width << ' ' << height << std::endl << "1" << std::endl;

    for(const auto &i : pixel)
    {
        out << i << ' ' << i << ' ' << i << ' ';
    }

    out.close();
}
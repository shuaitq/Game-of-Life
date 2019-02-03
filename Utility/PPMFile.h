#ifndef PPM_FILE_H_
#define PPM_FILE_H_

#include <string>
#include <vector>

class PPMFile
{
public:
    static void save(const std::string &path, const int &width, const int &height, const std::vector<bool> &pixel);
};

#endif // PPM_FILE_H_
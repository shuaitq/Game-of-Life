#ifndef RLE_FILE_H_
#define RLE_FILE_H_

#include <string>
#include <vector>
#include <array>

class RLEFile
{
public:
    static void read(const std::string &path, int &width, int &height, std::array<bool, 9> &born, std::array<bool, 9> &survive, std::vector<bool> &pixel);
};

#endif // RLE_FILE_H_
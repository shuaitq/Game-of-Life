#include "Utility/PPMFile.h"
#include "Utility/RLEFile.h"

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <unistd.h>

class Game
{
public:
    Game():width(0), height(0), time(0), born(), survive(), now(), past(){}
    void read(const std::string &path)
    {
        RLEFile::read(path, width, height, born, survive, now);
        past.resize(width * height);
    }
    void run()
    {
        for(int i = 1; i <= time; ++ i)
        {
            std::cout << "Starting: " << i << std::endl;
            swap(now, past);
            
            std::cout << "Saving" << std::endl;
            save(i);

            std::cout << "Calcing" << std::endl;
            calc();
        }
    }
private:
    void save(int t)
    {
        std::string path = "Output/";
        path += std::to_string(t);
        path += ".ppm";
        PPMFile::save(path, width, height, past);
    }

    void calc()
    {
        for(int i = 0; i < height; ++ i)
        {
            for(int j = 0; j < width; ++ j)
            {
                now[index(i, j)] = count(i, j);
            }
        }
    }

    int index(int x, int y)
    {
        return x * width + y;
    }

    bool count(int x, int y)
    {
        int count = past[index((x + 1) % height, (y + 1) % width)]
                    + past[index(x, (y + 1) % width)]
                    + past[index((x - 1 + height) % height, (y + 1) % width)]
                    + past[index((x + 1) % height, y)]
                    + past[index((x - 1 + height) % height, y)]
                    + past[index((x + 1) % height, (y - 1 + width) % width)]
                    + past[index(x, (y - 1  + width) % width)]
                    + past[index((x - 1 + height) % height, (y - 1 + width) % width)];
        
        if(past[index(x, y)] == true)
        {
            return survive[count];
        }
        else
        {
            return born[count];
        }
    }
public:
    int time;
private:
    int width, height;
    std::array<bool, 9> born, survive;
    std::vector<bool> now, past;
};

void usage()
{
    std::cout << "Usage: Game.out -p [PATTERN FILE] -t [SIMULATE TIMES]" << std::endl;
    std::cout << "Example: Game.out -p Pattern/otcametapixel.rle -t 100" << std::endl;
}

int main(int argc, char* argv[])
{
    int ret;
    bool time = false, pattern = false;
    Game g;

    while((ret = getopt(argc, argv, "hp:t:")) != -1)
    {
        switch(ret)
        {
        case 't':
            time = true;
            g.time = atoi(optarg);
            break;
        case 'p':
            pattern = true;
            g.read(optarg);
            break;
        case 'h':
        default:
            usage();
            return 0;
        }
    }

    if(time && pattern)
    {
        g.run();
    }
    else
    {
        usage();        
    }

    return 0;
}
#include "RLEFile.h"

#include <fstream>
#include <stdexcept>

enum class state
{
    head,       // x = 41, y = 49, rule = B3/S23
    body,       // 19b2o$19b4o$19bob2o2$20bo$19b2o$19b3o$21bo$33b2o$33b2o7$36bo$35b2o$34b
    end         // !
};

static void parse_string(std::string::const_iterator &it, const std::string &s)
{
    for(const auto &c : s)
    {
        if(*it != c)
        {
            std::string error("Expect: ");
            error += c;
            error += " Actual: ";
            error += *it;
            throw std::runtime_error(error);
        }
        ++ it;
    }
}

static void read_int(std::string::const_iterator &it, int &num)
{
    num = 0;

    while(*it <= '9' && *it >= '0')
    {
        num *= 10;
        num += *it - '0';
        ++ it;
    }
}

void RLEFile::read(const std::string &path, int &width, int &height, std::array<bool, 9> &born, std::array<bool, 9> &survive, std::vector<bool> &pixel)
{
    std::ifstream in(path);
    std::string line;
    state s = state::head;
    int row = 0, col = 0;

    if(!in.is_open())
    {
        std::string error("Can't open file: ");
        error += path;
        throw std::runtime_error(error);
    }

    while(std::getline(in, line))
    {
        if(line.length() > 0 && line[0] != '#')
        {
            if(s == state::head)
            {
                // x = 41, y = 49, rule = B3/S23
                auto it = line.cbegin();

                parse_string(it, "x = ");
                read_int(it, width);
                parse_string(it, ", y = ");
                read_int(it, height);
                parse_string(it, ", rule = ");

                if(*it == 'b' || *it == 'B')
                {
                    // rule = b3/s23
                    // rule = B3/S23
                    ++ it;
                    while(*it != '/')
                    {
                        born[*it - '0'] = true;
                        ++ it;
                    }
                    ++ it;

                    if(*it == 's' || *it == 'S')
                    {
                        ++ it;
                        while(*it <= '9' && *it >= '0')
                        {
                            survive[*it - '0'] = true;
                            ++ it;
                        }
                    }
                    else
                    {
                        std::string error("Expect: s or S Actual: ");
                        error += *it;
                        throw std::runtime_error(error);
                    }
                }
                else
                {
                    // rule = 23/3
                    // rule = s23/b3

                    if(*it == 's' || *it == 'S')
                    {
                        ++ it;
                    }

                    while(*it != '/')
                    {
                        survive[*it - '0'] = true;
                        ++ it;
                    }
                    ++ it;

                    if(*it == 'b' || *it == 'B')
                    {
                        ++ it;
                    }

                    while(*it <= '9' && *it >= '0')
                    {
                        born[*it - '0'] = true;
                        ++ it;
                    }
                }

                pixel.resize(width * height);
                s = state::body;
            }
            else if(s == state::body)
            {
                int count = 0;
                for(const auto &c : line)
                {
                    if(c <= '9' && c >= '0')
                    {
                        count *= 10;
                        count += c - '0';
                    }
                    else if(c == '!')
                    {
                        s = state::end;
                        break;
                    }
                    else
                    {
                        if(count == 0)
                        {
                            count = 1;
                        }

                        for(int i = 0; i < count; ++ i)
                        {
                            if(c == '$')
                            {
                                ++ row;
                                col = 0;
                            }
                            else if(c == 'o' || c == 'b')
                            {
                                if(c == 'o')
                                {
                                    pixel[row * width + col] = true;
                                }
                                
                                ++ col;
                            }
                        }

                        count = 0;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }

    in.close();
}
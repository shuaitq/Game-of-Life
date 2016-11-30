#ifndef PLANE_H_
#define PLANE_H_

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <fstream>
#include "bmp.h"
#include "json/document.h"
#include "json/istreamwrapper.h"

namespace plane{

    static const int LIVE=2;
    static const int KEEP=1;
    static const int DIE=0;
    static const int MAX_LENGTH=4096;

    using pixel=bool;

    class plane{
    public:
        plane();
        ~plane();
        void run();
        bool save(const char *path);
        bool read_json(const char *path);
    private:
        pixel **now,**past;
        int height,width,time;
        char path[MAX_LENGTH];
        char rules[9];
        void rand();
        void change();
        void calc();
        pixel count(int x,int y);
        void resize(int h,int w);
    };

}

#endif //PLANE_H_
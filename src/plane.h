#ifndef PLANE_H_
#define PLANE_H_

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>
#include "bmp.h"
#include "json/document.h"
#include "json/istreamwrapper.h"

namespace plane{

    const int LIVE=2;
    const int KEEP=1;
    const int DIE=0;

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
        char path[4096];
        char rules[9];
        void rand();
        void change();
        void calc();
        pixel count(int x,int y);
        void resize(int h,int w);
    };

}

#endif //PLANE_H_
#ifndef PLANE_H_
#define PLANE_H_

#include <cstdlib>
#include <string>
#include <ctime>
#include "bmp.h"
#include "config.h"
#include "json/document.h"
#include "json/istreamwrapper.h"

class plane{
public:
    plane();
    plane(int h,int w);
    ~plane();
    void run();
    void save(const char *path);
    bool read_json(const char *path);
private:
    pixel **now,**past;
    int height,width,time;
    std::string path;
    char rules[9];
    void rand();
    void change();
    void calc();
    pixel count(int x,int y);
    void resize(int h,int w);
    void set_rule(int i,char rule);
    void set(int x,int y,pixel data);
};

#endif /*PLANE_H_*/
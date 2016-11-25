#ifndef PLANE_H_
#define PLANE_H_

#include <cstdlib>
#include <ctime>
#include "bmp.h"
#include "config.h"

class plane{
public:
	plane();
	plane(int h,int w);
	~plane();
	void set(int x,int y,pixel data);
    void set_rule(int i,char rule);
	void rand();
	void change();
	void calc();
	void save(const char *path);
private:
    pixel **now,**past;
	int height,width;
	char rules[9];
    pixel count(int x,int y);
};

#endif /*PLANE_H_*/
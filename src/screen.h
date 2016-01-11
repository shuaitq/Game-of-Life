#ifndef SCREEN_H
#define SCREEN_H
#include "cell.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
struct screen{
    cell *pixels;
	int _s,_l;
	screen();
	screen(int s,int l);
	~screen();
	void init(int s,int l,cell *data);
    void print_n();
    void print_p();
    inline int count(int x,int y);
    inline bool liveordie(int x,int y);
	void rand();
	void load(const char *path);
	void print_info();
	void change();
	void calc();
	inline int xy(int x,int y);
	void resize(int s,int l);
};
#endif
#ifndef SCREEN_H
#define SCREEN_H
#include "cell.h"
#include "rules.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
struct screen{
    cell *pixels;
	int _h,_w;
	rules _ru;
	screen();
	screen(int h,int w);
	~screen();
	void set(int x,int y,cell data);
	void init(int h,int w,cell *data);
    inline int count(int x,int y){
		return (pixels[xy((x+1)%_h,(y+1)%_w)].past
				+pixels[xy(x,(y+1)%_w)].past
				+pixels[xy((x-1+_h)%_h,(y+1)%_w)].past
				+pixels[xy((x+1)%_h,y)].past
				+pixels[xy((x-1+_h)%_h,y)].past
				+pixels[xy((x+1)%_h,(y-1+_w)%_w)].past
				+pixels[xy(x,(y-1+_w)%_w)].past
				+pixels[xy((x-1+_h)%_h,(y-1+_w)%_w)].past);
	}
    inline bool liveordie(int x,int y){	
		int temp=count(x,y);
		switch(_ru._r[temp]){
			case 0:
				return false;
			case 1:
				return pixels[xy(x,y)].past;
			default:
				return true;
		}
	}
	void rand();
	void load_screen(const char *path);
	void load_rules(const char *path);
	void print_info();
	void change();
	void calc();
	inline int xy(int x,int y){
		return x*_w+y;
	}
	void resize(int h,int w);
};
#endif
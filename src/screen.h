#ifndef SCREEN_H
#define SCREEN_H
#include <cstdlib>
#include <ctime>
#include <vector>
#include "image.h"
#include "config.h"
struct screen{
    bool **now,**past;
	int height,width;
	int rules[9];
	BmpFileHeader file_header;
	BmpInfoHeader info_header;
	screen();
	screen(int h,int w);
	~screen();
	void Set(int x,int y,bool data);
	void Resize(int h,int w);
    inline bool CountAll(int x,int y){
		switch(rules[past[(x+1)%height][(y+1)%width]
				+past[x][(y+1)%width]
				+past[(x-1+height)%height][(y+1)%width]
				+past[(x+1)%height][y]
				+past[(x-1+height)%height][y]
				+past[(x+1)%height][(y-1+width)%width]
				+past[x][(y-1+width)%width]
				+past[(x-1+height)%height][(y-1+width)%width]]){
			case DIE:
				return false;
			case KEEP:
				return past[x][y];
			case LIVE:
				return true;
		}
	}
	void Rand();
	void Change();
	void Calc();
	void Save(const char *path);
};
#endif

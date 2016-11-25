#ifndef IMAGE_H_
#define IMAGE_H_

#include <cstdio>
#include "rgb.h"
#include "config.h"
#pragma pack(2)

struct file_header{
	uint16_t type;
	uint32_t size;
	uint32_t reserved;
	uint32_t off_bits;
};

struct info_header{
	uint32_t size;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bit_count;
	uint32_t compression;
	uint32_t size_image;
	uint32_t x_pels_per_meter;
	uint32_t y_pels_per_meter;
	uint32_t clr_used;
	uint32_t clr_important;
};

class bmp{
public:
    bmp(int h,int w,pixel **p);
	~bmp();
	void save(const char *path);
private:
	int height,width;
	pixel **pixels;
};

#endif /*IMAGE_H_*/
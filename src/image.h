#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <cstdio>
#pragma pack(2)
struct BmpFileHeader{
	uint16_t bf_type;
	uint32_t bf_size;
	uint32_t bf_reserved;
	uint32_t bf_off_bits;
};
struct BmpInfoHeader{
	uint32_t bi_size;
	uint32_t bi_width;
	uint32_t bi_height;
	uint16_t bi_planes;
	uint16_t bi_bit_count;
	uint32_t bi_compression;
	uint32_t bi_size_image;
	uint32_t bi_x_pels_per_meter;
	uint32_t bi_y_pels_per_meter;
	uint32_t bi_clr_used;
	uint32_t bi_clr_important;
};
struct RGB{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
	RGB(uint8_t r,uint8_t g,uint8_t b,uint8_t al);
};
const RGB black(0,0,0,0);
const RGB white(255,255,255,0);
struct BmpImage{
	int height,width;
	bool **pixels;
	BmpImage();
	BmpImage(int h,int w);
	~BmpImage();
	void Set(int x,int y,bool v);
	void SaveBmp(const char *path);
	void Resize(int h,int w);
};
#endif

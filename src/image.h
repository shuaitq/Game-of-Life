#ifndef IMAGE_H
#define IMAGE_H
#include <cstdint>
#include <cstdio>
#include <cstring>
#pragma pack(2)
struct BmpFileHeader{
	uint16_t bfType;
	uint32_t bfSize;
	uint32_t bfReserved;
	uint32_t bfOffBits;
};
struct BmpInfoHeader{
	uint32_t biSize;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biPlanes;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	uint32_t biXPelsPerMeter;
	uint32_t biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
};
struct RGB{
	bool bw;
	RGB();
	RGB(bool temp);
};
struct RGBQUAD{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t Re;
	RGBQUAD(uint8_t r,uint8_t g,uint8_t b,uint8_t re);
};
struct BmpImage{
	int _h,_w;
	RGB *_data;
	BmpImage();
	BmpImage(int height,int width);
	~BmpImage();
	void set(int x,int y,RGB v);
	void saveBmp(const char *path);
	void init(int height,int width,RGB *data);
	void resize(int height,int width,RGB *data);
	void resize(int height,int width);
	inline int xy(int x,int y){
		return x*_w+y;
	}
};
#endif
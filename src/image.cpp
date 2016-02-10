#include "image.h"
RGB::RGB(){
	bw=0;
}
RGB::RGB(bool temp){
	bw=temp;
}
RGBQUAD::RGBQUAD(uint8_t r,uint8_t g,uint8_t b,uint8_t re){
	R=r;
	G=g;
	B=b;
	Re=re;
}
BmpImage::BmpImage(){
	_h=0;
	_w=0;
	_data=NULL;
}
BmpImage::BmpImage(int height,int width){
	_data=NULL;
	init(height,width,NULL);
}
BmpImage::~BmpImage(){
	delete [] _data;
}
void BmpImage::set(int x,int y,RGB v){
	_data[xy(x,y)]=v;
}
void BmpImage::saveBmp(const char *path){
	BmpFileHeader FileHeader;
	BmpInfoHeader InfoHeader;
	FILE *fd=NULL;
	InfoHeader.biSize=sizeof(BmpInfoHeader);
	InfoHeader.biHeight=_h;
	InfoHeader.biWidth=_w;
	InfoHeader.biPlanes=1;
	InfoHeader.biBitCount=1;
	InfoHeader.biCompression=0;
	InfoHeader.biSizeImage=((_w+31)/32)*4*_h;
	InfoHeader.biXPelsPerMeter=2835;
	InfoHeader.biYPelsPerMeter=2835;
	InfoHeader.biClrUsed=0;
	InfoHeader.biClrImportant=0;
	int nBitsOffset=sizeof(BmpFileHeader)+InfoHeader.biSize+sizeof(RGBQUAD)*2;
	long lImageSize=InfoHeader.biSizeImage;
	long lFileSize=nBitsOffset+lImageSize;
	FileHeader.bfType='B'+('M'<<8);
	FileHeader.bfOffBits=nBitsOffset;
	FileHeader.bfSize=lFileSize;
	FileHeader.bfReserved=0;
	fd=fopen(path,"wb");
	fwrite(&FileHeader,1,sizeof(BmpFileHeader),fd);
	fwrite(&InfoHeader,1,sizeof(BmpInfoHeader),fd);
	RGBQUAD black(0,0,0,0),write(255,255,255,0);
	fwrite(&black,1,sizeof(RGBQUAD),fd);
	fwrite(&write,1,sizeof(RGBQUAD),fd);
	unsigned char temp;
	for(int i=0;i<_h;i++){
		for(int j=0;j<((_w+31)/32)*4;j++){
			temp=0;
			for(int k=0;k<8;k++){
				temp*=2;
				if(j*8+k<_w){
					if(_data[xy(i,j*8+k)].bw==true){
						temp+=1;
					}
				}
			}
			fwrite(&temp,1,1,fd);
		}
	}
	fclose(fd);
}
void BmpImage::init(int height,int width,RGB *data){
	if(_data){
		delete [] _data;
	}
	_h=height;
	_w=width;
	_data=new RGB[height*width];
	if(data){
		memcpy(_data,data,sizeof(RGB)*height*width);
	}
}
void BmpImage::resize(int height,int width,RGB *data){
	init(height,width,data);
}
void BmpImage::resize(int height,int width){
	init(height,width,NULL);
}

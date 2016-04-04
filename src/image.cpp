#include "image.h"
RGB::RGB(uint8_t r,uint8_t g,uint8_t b,uint8_t al){
	red=r;
	green=g;
	blue=b;
	alpha=al;
}
BmpImage::BmpImage(){
	height=0;
	width=0;
	pixels=NULL;
}
BmpImage::BmpImage(int h,int w){
	pixels=new bool*[h];
	for(int i=0;i<h;i++){
		pixels[i]=new bool[w];
	}
}
BmpImage::~BmpImage(){
	for(int i=0;i<height;i++){
		delete [] pixels[i];
	}
	delete [] pixels;
}
void BmpImage::Set(int x,int y,bool v){
	pixels[x][y]=v;
}
void BmpImage::SaveBmp(const char *path){
	BmpFileHeader file_header;
	BmpInfoHeader info_header;
	info_header.bi_size=sizeof(BmpInfoHeader);
	info_header.bi_height=height;
	info_header.bi_width=width;
	info_header.bi_planes=1;
	info_header.bi_bit_count=1;
	info_header.bi_compression=0;
	info_header.bi_size_image=((width+31)/32)*4*height;
	info_header.bi_x_pels_per_meter=2835;
	info_header.bi_y_pels_per_meter=2835;
	info_header.bi_clr_used=0;
	info_header.bi_clr_important=0;
	int n_bits_offset=sizeof(BmpFileHeader)+info_header.bi_size+sizeof(RGB)*2;
	long l_image_size=info_header.bi_size_image;
	long l_file_size=n_bits_offset+l_image_size;
	file_header.bf_type='B'+('M'<<8);
	file_header.bf_off_bits=n_bits_offset;
	file_header.bf_size=l_file_size;
	file_header.bf_reserved=0;
	FILE *fd=NULL;
	fd=fopen(path,"wb");
	fwrite(&file_header,1,sizeof(BmpFileHeader),fd);
	fwrite(&info_header,1,sizeof(BmpInfoHeader),fd);
	fwrite(&black,1,sizeof(RGB),fd);
	fwrite(&white,1,sizeof(RGB),fd);
	unsigned char temp;
	for(int i=0;i<height;i++){
		for(int j=0;j<((width+31)/32)*4;j++){
			temp=0;
			for(int k=0;k<8;k++){
				temp*=2;
				if(j*8+k<width){
					if(pixels[i][j*8+k]==true){
						temp+=1;
					}
				}
			}
			fwrite(&temp,1,1,fd);
		}
	}
	fclose(fd);
}
void BmpImage::Resize(int h,int w){
	if(pixels){
		for(int i=0;i<height;i++){
			delete [] pixels[i];
		}
		delete [] pixels;
	}
	height=h;
	width=w;
	pixels=new bool*[h];
	for(int i=0;i<h;i++){
		pixels[i]=new bool[w];
	}
}
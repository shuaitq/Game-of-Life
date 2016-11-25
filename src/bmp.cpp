#include "bmp.h"

bmp::bmp(int h,int w,pixel **p):height(h),width(w),pixels(p){}

bmp::~bmp(){
	for(int i=0;i<height;i++){
		delete [] pixels[i];
	}
	delete [] pixels;
}

void bmp::save(const char *path){
	file_header file;
	info_header info;
	info.size=sizeof(info_header);
	info.height=height;
	info.width=width;
	info.planes=1;
	info.bit_count=1;
	info.compression=0;
	info.size_image=((width+31)/32)*4*height;
	info.x_pels_per_meter=2835;
	info.y_pels_per_meter=2835;
	info.clr_used=0;
	info.clr_important=0;
	int n_bits_offset=sizeof(file_header)+info.size+sizeof(rgb)*2;
	long l_image_size=info.size_image;
	long l_file_size=n_bits_offset+l_image_size;
	file.type='B'+('M'<<8);
	file.off_bits=n_bits_offset;
	file.size=l_file_size;
	file.reserved=0;
	FILE *fd=nullptr;
	fd=fopen(path,"wb");
	fwrite(&file,1,sizeof(file_header),fd);
	fwrite(&info,1,sizeof(info_header),fd);
	fwrite(&black,1,sizeof(rgb),fd);
	fwrite(&white,1,sizeof(rgb),fd);
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
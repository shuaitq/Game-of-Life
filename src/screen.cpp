#include "screen.h"
screen::screen(){
	height=0;
	width=0;
	now=NULL;
	past=NULL;
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
	file_header.bf_type='B'+('M'<<8);
	file_header.bf_off_bits=sizeof(BmpFileHeader)+info_header.bi_size+sizeof(RGB)*2;
	file_header.bf_size=file_header.bf_off_bits+info_header.bi_size_image;
	file_header.bf_reserved=0;
}
screen::screen(int h,int w){
	height=h;
	width=w;
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
	file_header.bf_type='B'+('M'<<8);
	file_header.bf_off_bits=sizeof(BmpFileHeader)+info_header.bi_size+sizeof(RGB)*2;
	file_header.bf_size=file_header.bf_off_bits+info_header.bi_size_image;
	file_header.bf_reserved=0;
	now=new bool*[h];
	past=new bool*[h];
	for(int i=0;i<h;i++){
		now[i]=new bool[w];
		past[i]=new bool[w];
	}
}
screen::~screen(){
	for(int i=0;i<height;i++){
		delete [] now[i];
		delete [] past[i];
	}
	delete [] now;
	delete [] past;
}
void screen::Set(int x,int y,bool data){
	now[x][y]=data;
}
void screen::Resize(int h,int w){
	if(now!=NULL){
		for(int i=0;i<height;i++){
			delete [] now[i];
		}
		delete [] now;
	}
	if(past!=NULL){
		for(int i=0;i<height;i++){
			delete [] past[i];
		}
		delete [] past;
	}
	height=h;
	width=w;
	info_header.bi_height=height;
	info_header.bi_width=width;
	info_header.bi_size_image=((width+31)/32)*4*height;
	file_header.bf_size=file_header.bf_off_bits+info_header.bi_size_image;
	now=new bool*[h];
	past=new bool*[h];
	for(int i=0;i<h;i++){
		now[i]=new bool[w];
		past[i]=new bool[w];
	}
}
void screen::Rand(){
	srand(time(NULL));
	for(int i=0;i<height;i++){
		for(int j=0;j<width;j++){
			now[i][j]=std::rand()%2;
		}
	}
}
void screen::Change(){
	bool **temp=now;
	now=past;
	past=temp;
}
void screen::Calc(){
	//centre
	#pragma omp parallel for schedule(guided)
	for(int i=1;i<height-1;i++){
		for(int j=1;j<width-1;j++){
			switch(rules[past[i+1][j+1]
					+past[i][j+1]
					+past[i-1][j+1]
					+past[i+1][j]
					+past[i-1][j]
					+past[i+1][j-1]
					+past[i][j-1]
					+past[i-1][j-1]]){
				case DIE:
					now[i][j]=false;
					break;
				case KEEP:
					now[i][j]=past[i][j];
					break;
				case LIVE:
					now[i][j]=true;
					break;
			}
		}
	}
	//left
	#pragma omp parallel for schedule(guided)
	for(int i=1;i<height-1;i++){
		switch(rules[past[i+1][1]
				+past[i][1]
				+past[i-1][1]
				+past[i+1][0]
				+past[i-1][0]
				+past[i+1][width-1]
				+past[i][width-1]
				+past[i-1][width-1]]){
			case DIE:
				now[i][0]=false;
				break;
			case KEEP:
				now[i][0]=past[i][0];
				break;
			case LIVE:
				now[i][0]=true;
				break;
		}
	}
	//right
	#pragma omp parallel for schedule(guided)
	for(int i=1;i<height-1;i++){
		switch(rules[past[i+1][0]
				+past[i][0]
				+past[i-1][0]
				+past[i+1][width-1]
				+past[i-1][width-1]
				+past[i+1][width-2]
				+past[i][width-2]
				+past[i-1][width-2]]){
			case DIE:
				now[i][width-1]=false;
				break;
			case KEEP:
				now[i][width-1]=past[i][width-1];
				break;
			case LIVE:
				now[i][width-1]=true;
				break;
		}
	}
	//up
	#pragma omp parallel for schedule(guided)
	for(int i=1;i<width-1;i++){
		switch(rules[past[0][i+1]
				+past[height-1][i+1]
				+past[height-2][i+1]
				+past[0][i]
				+past[height-2][i]
				+past[0][i-1]
				+past[height-1][i-1]
				+past[height-2][i-1]]){
			case DIE:
				now[height-1][i]=false;
				break;
			case KEEP:
				now[height-1][i]=past[height-1][i];
				break;
			case LIVE:
				now[height-1][i]=true;
				break;
		}
	}
	//down
	#pragma omp parallel for schedule(guided)
	for(int i=1;i<width-1;i++){
		switch(rules[past[1][i+1]
				+past[0][i+1]
				+past[height-1][i+1]
				+past[1][i]
				+past[height-1][i]
				+past[1][i-1]
				+past[0][i-1]
				+past[height-1][i-1]]){
			case DIE:
				now[0][i]=false;
				break;
			case KEEP:
				now[0][i]=past[0][i];
				break;
			case LIVE:
				now[0][i]=true;
				break;
		}
	}
	now[0][0]=CountAll(0,0);
	now[0][width-1]=CountAll(0,width-1);
	now[height-1][0]=CountAll(height-1,0);
	now[height-1][width-1]=CountAll(height-1,width-1);
}
void screen::Save(const char *path){
	FILE *fd=fopen(path,"wb");
	fwrite(&file_header,sizeof(BmpFileHeader),1,fd);
	fwrite(&info_header,sizeof(BmpInfoHeader),1,fd);
	fwrite(&black,sizeof(RGB),1,fd);
	fwrite(&white,sizeof(RGB),1,fd);
	int len=(width+31)/32*4;
	unsigned char temp[len];
	for(int i=0;i<height;i++){
		for(int j=0;j<len-4;j++){
			temp[j]=past[i][j*8]<<7;
			temp[j]+=past[i][j*8+1]<<6;
			temp[j]+=past[i][j*8+2]<<5;
			temp[j]+=past[i][j*8+3]<<4;
			temp[j]+=past[i][j*8+4]<<3;
			temp[j]+=past[i][j*8+5]<<2;
			temp[j]+=past[i][j*8+6]<<1;
			temp[j]+=past[i][j*8+7];
		}
		for(int j=len-4;j<len;j++){
			temp[j]=0;
			for(int k=0;k<8;k++){
				temp[j]*=2;
				if(j*8+k<width){
					temp[j]+=past[i][j*8+k];
				}
			}
		}
		fwrite(&temp,sizeof(temp),1,fd);
	}
	fclose(fd);
}

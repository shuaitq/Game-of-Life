#include "bmp.h"

namespace bmp{

    rgb::rgb(uint8_t r,uint8_t g,uint8_t b,uint8_t al):red(r),green(g),blue(b),alpha(al){}

    bmp::bmp(uint32_t h,uint32_t w){
        init(h,w);
    }

    bmp::~bmp(){
        for(int i=0;i<height();i++){
            delete [] bytes[i];
        }
        delete [] bytes;
    }

    void bmp::set_pixel(uint32_t x,uint32_t y,pixel v){
        const byte temp=(1<<(7-y%8));
        if(v){
            bytes[x][y/8]|=temp;
        }else{
            bytes[x][y/8]&=~temp;
        }
    }

    bool bmp::save(const char *path)const{
        FILE *fp=fopen(path,"wb");
        if(fp==nullptr){
            return false;
        }
        fwrite(&file,sizeof(file_header),1,fp);
        fwrite(&info,sizeof(info_header),1,fp);
        fwrite(&black,sizeof(rgb),1,fp);
        fwrite(&white,sizeof(rgb),1,fp);
        for(int i=0;i<height();i++){
            fwrite(bytes[i],len(),1,fp);
        }
        fclose(fp);
        return true;
    }

    uint32_t bmp::height()const{
        return info.height;
    }

    uint32_t bmp::width()const{
        return info.width;
    }

    void bmp::init(uint32_t h,uint32_t w){
        info.size=sizeof(info_header);
        info.height=h;
        info.width=w;
        info.planes=1;
        info.bit_count=1;
        info.compression=0;
        info.size_image=((w+31)/32)*4*h;
        info.x_pels_per_meter=2835;
        info.y_pels_per_meter=2835;
        info.clr_used=0;
        info.clr_important=0;
        file.type='B'+('M'<<8);
        file.off_bits=sizeof(file_header)+info.size+sizeof(rgb)*2;
        file.size=file.off_bits+info.size_image;
        file.reserved=0;
        bytes=new byte*[h];
        for(int i=0;i<h;i++){
            bytes[i]=new byte[len()];
        }
    }

    uint32_t bmp::len()const{
        return info.size_image/info.height;
    }
}
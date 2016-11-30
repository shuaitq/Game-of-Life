#ifndef BMP_H_
#define BMP_H_

#include <cstdint>
#include <cstdio>
#pragma pack(2)

namespace bmp{

    using pixel=bool;
    using byte=uint8_t;

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
    
    class rgb{
    public:
        rgb(uint8_t r,uint8_t g,uint8_t b,uint8_t al);
    private:
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    };

    static const rgb black(0,0,0,0);
    static const rgb white(255,255,255,0);

    class bmp{
    public:
        bmp(uint32_t h,uint32_t w);
        ~bmp();
        void set_pixel(uint32_t x,uint32_t y,pixel v);
        bool save(const char *path)const;
        uint32_t height()const;
        uint32_t width()const;
    private:
        file_header file;
        info_header info;
        void init(uint32_t h,uint32_t w);
        uint32_t len()const;
        byte **bytes;
    };

}

#endif //BMP_H_
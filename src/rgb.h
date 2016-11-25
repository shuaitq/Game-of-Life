#ifndef RGB_H_
#define RGB_H_

#include <cstdint>

class rgb{
public:
	rgb(uint8_t r,uint8_t g,uint8_t b,uint8_t al);
private:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

#endif /*RGB_H_*/
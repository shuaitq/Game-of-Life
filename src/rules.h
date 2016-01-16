#ifndef RULES_H
#define RULES_H
const int DIE=0,KEEP=1,LIVE=2;
#include <cstring>
#include <cstdio>
struct rules{
	char _r[8];
	rules();
	void show();
};
#endif
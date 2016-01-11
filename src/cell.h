#ifndef CELL_H
#define CELL_H
struct cell{
	bool now,past;
	cell();
	cell(bool n,bool p);
};
#endif
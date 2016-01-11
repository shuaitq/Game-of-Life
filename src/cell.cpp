#include "cell.h"
cell::cell(){
	now=0;
	past=0;
}
cell::cell(bool n,bool p){
	now=n;
	past=p;
}
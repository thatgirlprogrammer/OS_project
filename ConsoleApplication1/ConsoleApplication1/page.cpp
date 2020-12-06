#include "page.h"
#include <iostream>

page::page() {
	//data1 = 0x0;
	//data2 = 0x0;
	//data3 = 0x0;
	//data4 = 0x0;
}

int32_t page::getData(int index) {
	if (index == 0) {
		return data1;
	}
	else if (index == 1) {
		return data2;
	}
	else if (index == 2) {
		return data3;
	}
	else {
		return data4;
	}
}

void page::writeData(int32_t d1, int32_t d2, int32_t d3, int32_t d4) {
	data1 = d1;
	data2 = d2;
	data3 = d3;
	data4 = d4;
	in_use = true;
}

bool page::inUse() {
	return in_use;
}
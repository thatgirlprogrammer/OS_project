#include "page.h"

page::page() {
	data1 = 0;
	data2 = 0;
	data3 = 0;
	data4 = 0;
}

uint32_t page::getData(int index) {
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

void page::writeData(uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4) {
	data1 = d1;
	data2 = d2;
	data3 = d3;
	data4 = d4;
	in_use = true;
}

bool page::inUse() {
	return in_use;
}
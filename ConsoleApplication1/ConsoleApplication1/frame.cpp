#include "frame.h"
#include <iostream>

frame::frame() {
	
}

int32_t frame::getData(int index) {
	mtx.lock();
	uint8_t data[4] = {0, 0, 0, 0 };
	if (index == 0) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data1[i];
		}
	}
	else if (index == 1) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data2[i];
		}
	}
	else if (index == 2) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data3[i];
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			data[i] = data4[i];
		}
	}
	int32_t result = (int)data[0] << 24;
	result |= (int)data[1] << 16;
	result |= (int)data[2] << 8;
	result |= (int)data[3];
	mtx.unlock();
	return result;
}

void frame::writeData(int32_t d1, int32_t d2, int32_t d3, int32_t d4) {
	mtx.lock();
	data1[0] = d1 >> 24;
	data1[1] = d1 >> 16;
	data1[2] = d1 >> 8;
	data1[3] = d1;

	data2[0] = d2 >> 24;
	data2[1] = d2 >> 16;
	data2[2] = d2 >> 8;
	data2[3] = d2;

	data3[0] = d3 >> 24;
	data3[1] = d3 >> 16;
	data3[2] = d3 >> 8;
	data3[3] = d3;

	data4[0] = d4 >> 24;
	data4[1] = d4 >> 16;
	data4[2] = d4 >> 8;
	data4[3] = d4;

	in_use = true;
	mtx.unlock();
}

bool frame::inUse() {
	return in_use;
}

void frame::setUse() {
	in_use = false;
}
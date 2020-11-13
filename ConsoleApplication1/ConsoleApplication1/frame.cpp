#include "frame.h"
#include <iostream>

frame::frame() {
	
}

int32_t frame::getData(int index) {
	int8_t data[4] = {0, 0, 0, 0 };
	if (index == 0) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data1[i];
			std::cout << "Data is " << data[i];
		}
	}
	else if (index == 1) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data2[i];
			std::cout << "Data is " << data[i];
		}
	}
	else if (index == 2) {
		for (int i = 0; i < 4; ++i) {
			data[i] = data3[i];
			std::cout << "Data is " << data[i];
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			data[i] = data4[i];
			std::cout << "Data is " << data[i];
		}
	}
	//mtx.lock();
	int32_t result = data[0] << 24;
	result |= data[1] << 16;
	result |= data[2] << 8;
	result |= data[3];
	//mtx.unlock();
	std::cout << "The result is " << result << std::endl;
	return result;
}

void frame::writeData(int32_t d1, int32_t d2, int32_t d3, int32_t d4) {
	mtx.lock();
	std::cout << "Writing data: ";
	data1[0] = d1 >> 24;
	data1[1] = d1 >> 16;
	data1[2] = d1 >> 8;
	data1[3] = d1;
	std::cout << (int32_t)data1[0] << (int32_t)data1[1] << (int32_t)data1[2] << (int32_t)data1[3] << " ";

	data2[0] = d2 >> 24;
	data2[1] = d2 >> 16;
	data2[2] = d2 >> 8;
	data2[3] = d2;

	std::cout << (int32_t)data2[0] << (int32_t)data2[1] << (int32_t)data2[2] << (int32_t)data2[3] << " ";

	data3[0] = d3 >> 24;
	data3[1] = d3 >> 16;
	data3[2] = d3 >> 8;
	data3[3] = d3;

	std::cout << (int32_t)data3[0] << (int32_t)data3[1] << (int32_t)data3[2] << (int32_t)data3[3] << " ";

	data4[0] = d4 >> 24;
	data4[1] = d4 >> 16;
	data4[2] = d4 >> 8;
	data4[3] = d4;

	std::cout << (int32_t)data4[0] << (int32_t)data4[1] << (int32_t)data4[2] << (int32_t)data4[3] << " " << std::endl;

	in_use = true;
	mtx.unlock();
}

bool frame::inUse() {
	return in_use;
}

void frame::setUse() {
	in_use = false;
}
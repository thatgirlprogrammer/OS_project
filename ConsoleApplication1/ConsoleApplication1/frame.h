#pragma once
#include <cstddef>
#include <cstdint>
#include <mutex>
class frame
{
public:
	frame();
	int32_t getData(int index);
	void writeData(int32_t d1, int32_t d2, int32_t d3, int32_t d4);
	bool inUse();
	void setUse();
private:
	uint8_t data1[4] = {0, 0, 0, 0};
	uint8_t data2[4]= {0, 0, 0, 0};
	uint8_t data3[4] = { 0, 0, 0, 0 };
	uint8_t data4[4] = { 0, 0, 0, 0 };
	bool in_use = false;
	std::mutex mtx;
};


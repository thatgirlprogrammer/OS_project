#pragma once
#include <cstddef>
#include <cstdint>
#include <mutex>
class frame
{
public:
	frame();
	uint32_t getData(int index);
	void writeData(uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4);
	bool inUse();
	void setUse();
private:
	int8_t data1[4];
	int8_t data2[4];
	int8_t data3[4];
	int8_t data4[4];
	bool in_use = false;
	std::mutex mtx;
};


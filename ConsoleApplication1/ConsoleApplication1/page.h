#pragma once
#include <cstddef>
#include <cstdint>
class page
{
public:
	page();
	uint32_t getData(int index);
	void writeData(uint32_t d1, uint32_t d2, uint32_t d3, uint32_t d4);
	bool inUse();
private:
	uint32_t data1;
	uint32_t data2;
	uint32_t data3;
	uint32_t data4;
	bool in_use = false;
};


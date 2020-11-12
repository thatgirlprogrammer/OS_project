#pragma once
#include <cstddef>
#include <cstdint>
class page
{
public:
	page();
	int32_t getData(int index);
	void writeData(int32_t d1, int32_t d2, int32_t d3, int32_t d4);
	bool inUse();
private:
	int32_t data1 = 0;
	int32_t data2 = 0;
	int32_t data3 = 0;
	int32_t data4 = 0;
	bool in_use = false;
};


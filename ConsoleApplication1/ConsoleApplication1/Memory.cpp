#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(int num, int offset) {
	int32_t result = fr[num]->getData(offset);
	return result;
}

bool Memory::isOccupied(int num) {
	return fr[num]->inUse();
}

void Memory::setMem(int num, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
	fr[num]->writeData(data1, data2, data3, data4);
}

void Memory::deallocate(int num) {
	fr[num]->setUse();
}

std::string Memory::dump() {
	using namespace std;
	std::stringstream output;
	output << "      00       04       08       0c" << std::endl;
	int k = 0;
	for (int i = 0; i < MEMORY; i += 16) {
		int32_t value = fr[k]->getData(0);
		output << setfill('0') << setw(3) << right << hex << i << " | ";
		uint8_t small_value = value >> 24;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 16;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 8;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;

		output << " ";
		value = fr[k]->getData(1);
	//	output << setfill('0') << setw(3) << right << hex << i << " | ";
		small_value = value >> 24;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 16;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 8;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;

		output << " ";
		value = fr[k]->getData(2);
	//	output << setfill('0') << setw(3) << right << hex << i << " | ";
		small_value = value >> 24;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 16;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 8;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;

		output << " ";
		
		value = fr[k]->getData(3);
	//	output << setfill('0') << setw(3) << right << hex << i << " | ";
		small_value = value >> 24;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 16;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value >> 8;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		small_value = value;
		output << setfill('0') << setw(2) << right << hex << (int)small_value;
		output << dec << endl;
		++k;
	}
	return output.str();
}

bool Memory::hasHole(int pages) {
	int current = 0;
	for (int i = 0; i < 256; ++i) {
		if (!fr[i]->inUse()) {
			current++;
		}
		if (current >= pages) {
			return true;
		}
	}
	return false;	
}

int Memory::freeFrame() {
	for (int i = 0; i < 256; ++i) {
		if (!fr[i]->inUse()) {
			return i;
		}
	}
	return -1;
}
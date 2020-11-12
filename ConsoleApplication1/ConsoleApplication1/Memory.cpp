#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(int num, int offset) {
	uint32_t result = fr[num].getData(offset);
	return result;
}

bool Memory::isOccupied(int num) {
	return fr[num].inUse();
}

void Memory::setMem(int num, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
	fr[num].writeData(data1, data2, data2, data4);
}

void Memory::deallocate(int num) {
	fr[num].setUse();
}

/*
std::string Memory::dump() {
	using namespace std;
	std::stringstream output;
	output << "      00       04       08       0c" << std::endl;
	for (int i = 0; i < MEMORY; i += 16) {
		output << setfill('0') << setw(3) << right << hex << i << " | ";
		for (int j = i; j < i + 4; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)this->memory[j];
		}
		output << " ";
		for (int j = i + 4; j < i + 8; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)this->memory[j];
		}
		output << " ";
		for (int j = i + 8; j < i + 12; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)this->memory[j];
		}
		output << " ";
		for (int j = i + 12; j < i + 16; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)this->memory[j];
		}
		output << dec << endl;
	}
	return output.str();
}*/

bool Memory::hasHole(int pages) {
	int current = 0;
	for (int i = 0; i < 256; ++i) {
		if (!fr[i].inUse()) {
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
		if (!fr[i].inUse()) {
			return i;
		}
	}
}
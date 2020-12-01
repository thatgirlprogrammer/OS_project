#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(int num, int offset) {
	int32_t result = fr[num].getData(offset);
	return result;
}

bool Memory::isOccupied(int num) {
	return fr[num].inUse();
}

void Memory::setMem(int num, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
//	std::cout << "Doing memory " << std::endl;
	fr[num].writeData(data1, data2, data3, data4);
//	std::cout << "Memory in frame now: ";
//	std::cout << fr[num].getData(0) << " ";
//	std::cout << fr[num].getData(1) << " ";
//	std::cout << fr[num].getData(2) << " ";
//	std::cout << fr[num].getData(3) << " ";
//	std::cout << std::endl;
}

void Memory::deallocate(int num) {
	fr[num].setUse();
}


std::string Memory::dump() {
	using namespace std;
	std::stringstream output;
	output << "      00       04       08       0c" << std::endl;
	int k = 0;
	for (int i = 0; i < MEMORY; i += 16) {
		output << setfill('0') << setw(3) << right << hex << i << " | ";
		for (int j = i; j < i + 4; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)fr[k].getData(j);
		}
		output << " ";
		++k;
		for (int j = i + 4; j < i + 8; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)fr[k].getData(j);
		}
		++k;
		output << " ";
		for (int j = i + 8; j < i + 12; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)fr[k].getData(j);
		}
		++k;
		output << " ";
		for (int j = i + 12; j < i + 16; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)fr[k].getData(j);
		}
		output << dec << endl;
		++k;
	}
	return output.str();
}

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
	return -1;
}
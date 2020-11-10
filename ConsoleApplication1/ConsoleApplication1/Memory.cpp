#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(uint16_t frame, uint16_t offset) {
	mtx.lock();
	//assert(frame % 4 == 0);
	int32_t result = this->memory[frame * 4 + offset] << 24;
	result |= this->memory[frame * 4 + offset + 1] << 16;
	result |= this->memory[frame * 4 + offset + 2] << 8;
	result |= this->memory[frame * 4 + offset + 3];
	mtx.unlock();
	return result;
}

bool Memory::isOccupied(uint16_t frame) {
	assert(frame % 4 == 0);
	bool result = this->free[frame];
	return result;
}

void Memory::setMem(uint16_t frame, int32_t data1, int32_t data2, int32_t data3, int32_t data4) {
	mtx.lock();
	frame = frame * 4;
	this->memory[frame] = data1 >> 24;
	this->memory[frame + 1] = data1 >> 16;
	this->memory[frame + 2] = data1 >> 8;
	this->memory[frame + 3] = data1;

	this->memory[frame + 4] = data2 >> 24;
	this->memory[frame + 5] = data2 >> 16;
	this->memory[frame + 6] = data2 >> 8;
	this->memory[frame + 7] = data2;

	this->memory[frame + 8] = data3 >> 24;
	this->memory[frame + 9] = data3 >> 16;
	this->memory[frame + 10] = data3 >> 8;
	this->memory[frame + 11] = data3;

	this->memory[frame + 12] = data4 >> 24;
	this->memory[frame + 13] = data4 >> 16;
	this->memory[frame + 14] = data4 >> 8;
	this->memory[frame + 15] = data4;
	mtx.unlock();
}

void Memory::allocate(uint16_t frame) {
	mtx.lock();
	assert(frame % 4 == 0);
	if (this->free[frame] != true) {
		in_use += 16;
	}

	this->free[frame] = true;
	this->free[frame + 1] = true;
	this->free[frame + 2] = true;
	this->free[frame + 3] = true;

	this->free[frame + 4] = true;
	this->free[frame + 5] = true;
	this->free[frame + 6] = true;
	this->free[frame + 7] = true;

	this->free[frame + 8] = true;
	this->free[frame + 9] = true;
	this->free[frame + 10] = true;
	this->free[frame + 11] = true;

	this->free[frame + 12] = true;
	this->free[frame + 13] = true;
	this->free[frame + 14] = true;
	this->free[frame + 15] = true;
	
	mtx.unlock();
}

void Memory::deallocate(uint16_t frame) {
	mtx.lock();
	assert(frame % 4 == 0);
	if (this->free[frame] != false) {
		in_use -= 16;
	}
	this->free[frame] = false;
	this->free[frame + 1] = false;
	this->free[frame + 2] = false;
	this->free[frame + 3] = false;

	this->free[frame + 4] = false;
	this->free[frame + 5] = false;
	this->free[frame + 6] = false;
	this->free[frame + 7] = false;

	this->free[frame + 8] = false;
	this->free[frame + 9] = false;
	this->free[frame + 10] = false;
	this->free[frame + 11] = false;

	this->free[frame + 12] = false;
	this->free[frame + 13] = false;
	this->free[frame + 14] = false;
	this->free[frame + 15] = false;

	mtx.unlock();
}

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
}

bool Memory::hasHole(int size) {
	uint16_t current = 0;
	int hole = 0;
	while (current < 1024) {
		if (isOccupied(current * 4) != false) {
			hole = 0;
		}
		else {
			++hole;
		}
		if (hole >= size) {
			return true;
		}
		++current;
	}
	return false;
}

uint16_t Memory::holeStart(int size) {
	int current = 0;
	int start = 0;
	int hole = 0;
	while (current < 1024) {
		if (isOccupied(current * 4) != false) {
			hole = 0;
			++current;
			start = current;
		}
		else {
			++hole;
		}
		if (hole >= size) {
			++current;
			return start + 1;
		}
		++current;
	}
	++current;
	return start + 1;
}

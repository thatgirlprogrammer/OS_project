#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(uint16_t addr) {
	mtx.lock();
	assert(addr % 4 == 0);
	int32_t result = this->memory[addr] << 24;
	result |= this->memory[addr + 1] << 16;
	result |= this->memory[addr + 2] << 8;
	result |= this->memory[addr + 3];
	mtx.unlock();
	return result;
}

bool Memory::isOccupied(uint16_t addr) {
	assert(addr % 4 == 0);
	bool result = this->free[addr];
	return result;
}

void Memory::setMem(uint16_t addr, int32_t data) {
	mtx.lock();
	assert(addr % 4 == 0);
	this->memory[addr] = data >> 24;
	this->memory[addr + 1] = data >> 16;
	this->memory[addr + 2] = data >> 8;
	this->memory[addr + 3] = data;
	mtx.unlock();
}

void Memory::allocate(uint16_t addr) {
	mtx.lock();
	assert(addr % 4 == 0);
	if (this->free[addr] != true) {
		in_use += 4;
	}

	this->free[addr] = true;
	this->free[addr + 1] = true;
	this->free[addr + 2] = true;
	this->free[addr + 3] = true;
	
	mtx.unlock();
}

void Memory::deallocate(uint16_t addr) {
	mtx.lock();
	assert(addr % 4 == 0);
	if (this->free[addr] != false) {
		in_use -= 4;
	}
	this->free[addr] = false;
	this->free[addr + 1] = false;
	this->free[addr + 2] = false;
	this->free[addr + 3] = false;

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
			std::cout << "\n" << start;
			++current;
			return start + 1;
		}
		++current;
	}
	std::cout << "\n" << start;
	++current;
	return start + 1;
}

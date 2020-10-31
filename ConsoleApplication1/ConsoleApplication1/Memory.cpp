#include <assert.h>
#include <iostream>
#include <iomanip>
#include "Memory.h"

int32_t Memory::getMem(uint16_t addr) {
	assert(addr % 4 == 0);

	// TODO: get offset from PCB
	int32_t result = this->memory[addr] << 24;
	result |= this->memory[addr + 1] << 16;
	result |= this->memory[addr + 2] << 8;
	result |= this->memory[addr + 3];
	return result;
}

bool Memory::isOccupied(uint16_t addr) {
	assert(addr % 4 == 0);

	bool result = this->free[addr];

	return result;
}

void Memory::setMem(uint16_t addr, int32_t data) {
	assert(addr % 4 == 0);

	// TODO: get offset from PCB
	this->memory[addr] = data >> 24;
	this->memory[addr + 1] = data >> 16;
	this->memory[addr + 2] = data >> 8;
	this->memory[addr + 3] = data;
}

void Memory::allocate(uint16_t addr) {
	assert(addr % 4 == 0);

	this->free[addr] = true;
	this->free[addr + 1] = true;
	this->free[addr + 2] = true;
	this->free[addr + 3] = true;
	in_use += 4;
}

void Memory::deallocate(uint16_t addr) {
	assert(addr % 4 == 0);

	this->free[addr] = false;
	this->free[addr + 1] = false;
	this->free[addr + 2] = false;
	this->free[addr + 3] = false;
	in_use -= 4;
}

std::string Memory::dump() {
	using namespace std;
	std::stringstream output;
	output << "      00       04       08       0c" << std::endl;
	for (int i = 0; i < MEMORY; i += 16) {
		output << setfill('0') << setw(3) << right << hex << i << " | ";
		//printf("%03x | ", i);
		for (int j = i; j < i + 4; j++) {
			output << setfill('0') << setw(2) << right << hex << (int)this->memory[j];
			//printf("%02x", this->memory[j]);
		}
		output << " ";
		//printf(" ");
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
		output << endl;
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
			return start;
		}
		++current;
	}
	std::cout << "\n" << start;
	++current;
	return start;
}

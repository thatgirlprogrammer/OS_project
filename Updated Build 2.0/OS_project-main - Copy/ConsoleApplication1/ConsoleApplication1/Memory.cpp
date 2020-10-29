#include <assert.h>
#include <iostream>
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

	this->free[addr] = true;
	this->free[addr + 1] = true;
	this->free[addr + 2] = true;
	this->free[addr + 3] = true;
}

void Memory::dump() {
	printf("      00       04       08       0c\n");
	for (int i = 0; i < MEMORY; i += 16) {
		printf("%03x | ", i);
		for (int j = i; j < i + 4; j++) {
			printf("%02x", this->memory[j]);
		}
		printf(" ");
		for (int j = i + 4; j < i + 8; j++) {
			printf("%02x", this->memory[j]);
		}
		printf(" ");
		for (int j = i + 8; j < i + 12; j++) {
			printf("%02x", this->memory[j]);
		}
		printf(" ");
		for (int j = i + 12; j < i + 16; j++) {
			printf("%02x", this->memory[j]);
		}
		printf("\n");
	}
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
			start = current;
		}
		else {
			++hole;
		}
		if (hole >= size) {
			return start;
		}
		++current;
	}
	return start;
}

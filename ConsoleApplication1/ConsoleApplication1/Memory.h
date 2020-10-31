#pragma once

#include <string>
#include <sstream>
#include <cstdint>

constexpr uint8_t REGISTER_COUNT = 16;
constexpr uint32_t MEMORY = 1024 * 4;

class Memory
{
public:
	Memory() {
		for (uint32_t i = 0; i < MEMORY; i++)
			this->memory[i] = 0;
	}

	int32_t getMem(uint16_t);
	void setMem(uint16_t addr, int32_t data);
	bool hasHole(int size);
	bool isOccupied(uint16_t addr);
	void allocate(uint16_t addr);
	void deallocate(uint16_t addr);
	uint16_t holeStart(int size);
	std::string dump();
	unsigned long in_use = 0;
private:
	uint8_t memory[MEMORY];
	bool free[MEMORY] = { false };
};

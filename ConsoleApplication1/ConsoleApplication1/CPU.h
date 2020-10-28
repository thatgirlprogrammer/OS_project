#pragma once

#include "instruction.h"

constexpr uint8_t REGISTER_COUNT = 16;
constexpr uint32_t MEMORY = 1024 * 4;

class CPU
{
public:
	CPU();

	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);

	void step();

	uint32_t getPC() { return this->pc; }
	bool isDone() { return this->done; }

	int32_t getMem(uint16_t);
	void setMem(uint16_t addr, int32_t data);
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	uint8_t memory[MEMORY];
	bool done = false;
};


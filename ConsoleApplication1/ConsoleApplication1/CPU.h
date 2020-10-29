#pragma once

#include "instruction.h"
#include "Memory.h"

class CPU
{
public:
	CPU(Memory*);

	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);

	void step();

	uint32_t getPC() { return this->pc; }
	bool isDone() { return this->done; }
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	bool done = false;
	Memory* memory;
};

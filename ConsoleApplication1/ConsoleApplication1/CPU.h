#pragma once

#include "instruction.h"
#include "Memory.h"
#include "DMA.h"

class CPU
{
public:
	CPU(Memory*, DMA*);

	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);

	void step();

	uint32_t getPC() { return this->pc; }
	void setPC() { pc = 0 + (this->base * 4); }
	void setBase(int b) { base = b; }
	bool isDone() { return this->done; }
	void setDone() { this->done = false; }
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	uint32_t base;
	bool done = false;
	Memory* memory;
	DMA* dma;
};

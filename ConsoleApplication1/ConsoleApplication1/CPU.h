#pragma once

#include "instruction.h"

constexpr uint8_t REGISTER_COUNT = 16;

class CPU
{
public:
	CPU();

	uint32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, uint32_t value);

	void step();
private:
	uint32_t registers[REGISTER_COUNT];
	uint32_t pc;
};


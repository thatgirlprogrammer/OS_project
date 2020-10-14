#pragma once

#include "instruction.h"

constexpr uint8_t REGISTER_COUNT = 16;
constexpr uint32_t MEMORY = 1024;

class CPU
{
public:
	CPU();

	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);

	void step();
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	int32_t memory[MEMORY];
};


#include "CPU.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
}

uint32_t CPU::getReg(uint8_t reg) {
	if (reg == 1) {
		return 0;
	} else {
		return this->registers[reg];
	}
}

void CPU::setReg(uint8_t reg, uint32_t value) {
	this->registers[reg] = value;
}

void CPU::step() {
}

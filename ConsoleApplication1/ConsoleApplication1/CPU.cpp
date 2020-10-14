#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	for (uint32_t i = 0; i < MEMORY; i++)
		this->memory[i] = 0;
	this->pc = 0;
}

int32_t CPU::getReg(uint8_t reg) {
	if (reg == 1) {
		return 0;
	} else {
		return this->registers[reg];
	}
}

void CPU::setReg(uint8_t reg, int32_t value) {
	this->registers[reg] = value;
}

void CPU::step() {
	// get program counter from PCB
	// TODO: offset
	Instruction i = Instruction(this->memory[this->pc++]);

	switch (i.opcode()) {
	case Opcode::MOV: {
		// idk which reg is supposed to be moved so I'll just use s1...
		uint32_t movs1 = this->getReg(i.arithS1());
		this->setReg(i.arithD(), movs1);
	} break;

	case Opcode::ADD: {
		uint32_t adds1 = this->getReg(i.arithS1());
		uint32_t adds2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), adds1 + adds2);
	} break;

	case Opcode::SUB: {
		uint32_t subs1 = this->getReg(i.arithS1());
		uint32_t subs2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), subs1 - subs2);
	} break;

	case Opcode::MUL: {
		uint32_t muls1 = this->getReg(i.arithS1());
		uint32_t muls2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), muls1 * muls2);
	} break;

	case Opcode::DIV: {
		uint32_t divs1 = this->getReg(i.arithS1());
		uint32_t divs2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), divs1 / divs2);
	} break;

	case Opcode::AND: {
		uint32_t ands1 = this->getReg(i.arithS1());
		uint32_t ands2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), ands1 & ands2);
	} break;

	case Opcode::OR: {
		uint32_t ors1 = this->getReg(i.arithS1());
		uint32_t ors2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), ors1 | ors2);
	} break;

	case Opcode::SLT: {
		uint32_t slts1 = this->getReg(i.arithS1());
		uint32_t slts2 = this->getReg(i.arithS2());

		// ???
		uint32_t data1 = this->memory[slts1];
		uint32_t data2 = this->memory[slts2];

		if (data1 < data2) {
			this->setReg(i.arithD(), 1);
		} else {
			this->setReg(i.arithD(), 0);
		}
	} break;

	case Opcode::HLT:
		// set process state to finished
		break;

	case Opcode::NOP:
		break;

	case Opcode::JMP: {
		this->pc = i.longAddr();
	} break;

	case Opcode::BEQ: {
		uint32_t beqb = this->getReg(i.cimmB());
		uint32_t beqd = this->getReg(i.cimmD());

		if (beqb == beqd) {
			this->pc = i.shortAddr();
		}

	} break;

	case Opcode::BNE: {
		uint32_t bneb = this->getReg(i.cimmB());
		uint32_t bned = this->getReg(i.cimmD());

		if (bneb != bned) {
			this->pc = i.shortAddr();
		}

	} break;

	case Opcode::BEZ: {
		uint32_t bezb = this->getReg(i.cimmB());

		if (bezb == 0) {
			this->pc = i.shortAddr();
		}

	} break;

	case Opcode::BNZ: {
		uint32_t bnzb = this->getReg(i.cimmB());

		if (bnzb != 0) {
			this->pc = i.shortAddr();
		}

	} break;

	case Opcode::BGZ: {
		uint32_t bgzb = this->getReg(i.cimmB());

		if (bgzb > 0) {
			this->pc = i.shortAddr();
		}

	} break;

	case Opcode::BLZ: {
		uint32_t blzb = this->getReg(i.cimmB());

		if (blzb < 0) {
			this->pc = i.shortAddr();
		}

	} break;

	default:
		std::cout << "unknown instruction" << std::endl;
		disassembleInstruction(i);
	}
}

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
	case Opcode::RD: {
		int32_t rdr1 = this->getReg(i.ioR1());
		int32_t rdr2 = this->getReg(i.ioR2());
		uint32_t rdaddr = i.shortAddr();

		// assuming the same rules as immediate instructions, if r2 is 0,
		// read from the address instead of the register
		int32_t data;
		if (rdr2 == 0) {
			data = this->memory[rdaddr];
		} else {
			data = this->memory[rdr2];
		}

		this->setReg(rdr1, data);
	} break;

	case Opcode::WR: {
		int32_t wrr1 = this->getReg(i.ioR1());
		// good luck luke xd
	} break;

	case Opcode::LW: {
		int32_t addr = this->getReg(i.cimmB());
		uint32_t lwd = i.cimmD();

		// LW and ST are never used with a non-zero shortAddr, and it's unspecified
		// what they would do with a non-zero shortAddr, so this is the best I've got

		this->setReg(lwd, this->memory[addr]);
	} break;

	case Opcode::ST: {
		int32_t data = this->getReg(i.cimmB());
		int32_t addr = this->getReg(i.cimmD());

		this->memory[addr] = data;
	} break;

	case Opcode::MOV: {
		// idk which reg is supposed to be moved so I'll just use s1...
		int32_t movs1 = this->getReg(i.arithS1());
		this->setReg(i.arithD(), movs1);
	} break;

	case Opcode::ADD: {
		int32_t adds1 = this->getReg(i.arithS1());
		int32_t adds2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), adds1 + adds2);
	} break;

	case Opcode::SUB: {
		int32_t subs1 = this->getReg(i.arithS1());
		int32_t subs2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), subs1 - subs2);
	} break;

	case Opcode::MUL: {
		int32_t muls1 = this->getReg(i.arithS1());
		int32_t muls2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), muls1 * muls2);
	} break;

	case Opcode::DIV: {
		int32_t divs1 = this->getReg(i.arithS1());
		int32_t divs2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), divs1 / divs2);
	} break;

	case Opcode::AND: {
		int32_t ands1 = this->getReg(i.arithS1());
		int32_t ands2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), ands1 & ands2);
	} break;

	case Opcode::OR: {
		int32_t ors1 = this->getReg(i.arithS1());
		int32_t ors2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), ors1 | ors2);
	} break;

	case Opcode::MOVI: {
		uint32_t movib = i.cimmB();
		uint32_t movid = i.cimmD();

		// if the d-reg is 0, the short addr (last 16 bits) contains data
		if (movid == 0) {
			// which is moved into the b-reg? the spec isn't clear
			this->setReg(movib, i.shortAddr());
		} else {
			this->setReg(movid, this->memory[i.shortAddr() + movid]);
		}
	} break;

		// addi muli divi ldi

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

		// slti

	case Opcode::HLT:
		// set process state to finished
		break;

	case Opcode::NOP:
		break;

	case Opcode::JMP: {
		this->pc = i.longAddr();
	} break;

	case Opcode::BEQ: {
		int32_t beqb = this->getReg(i.cimmB());
		int32_t beqd = this->getReg(i.cimmD());

		if (beqb == beqd) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BNE: {
		int32_t bneb = this->getReg(i.cimmB());
		int32_t bned = this->getReg(i.cimmD());

		if (bneb != bned) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BEZ: {
		int32_t bezb = this->getReg(i.cimmB());

		if (bezb == 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BNZ: {
		int32_t bnzb = this->getReg(i.cimmB());

		if (bnzb != 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BGZ: {
		int32_t bgzb = this->getReg(i.cimmB());

		if (bgzb > 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BLZ: {
		int32_t blzb = this->getReg(i.cimmB());

		if (blzb < 0) {
			this->pc = i.shortAddr();
		}
	} break;

	default:
		std::cout << "unknown instruction" << std::endl;
		disassembleInstruction(i);
	}
}

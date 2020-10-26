#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	// need to use actual memory
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
		uint8_t r1 = i.ioR1();
		int32_t r2 = this->getReg(i.ioR2());
		uint32_t rdaddr = i.shortAddr();

		// assuming the same rules as immediate instructions, if r2 is 0,
		// read from the address instead of the register
		int32_t data;
		if (r2 == 0) {
			data = this->memory[rdaddr];
		} else {
			data = this->memory[r2];
		}

		this->setReg(r1, data);
	} break;

	case Opcode::WR: {
		std::cout << "WR" << std::endl;
		uint32_t wrr1 = this->getReg(i.get_val1());
		uint8_t wrr2 = i.get_val2();
		uint32_t wraddr = i.get_val3();

		int32_t data;
		if (wrr1 == 0) {
			data = this->memory[wraddr];
		}
		else {
			data = this->memory[wrr1];
		}

		this->setReg(wrr2, data);
	} break;

	case Opcode::LW: {
		int32_t addr = this->getReg(i.cimmB());
		uint32_t d = i.cimmD();

		// LW and ST are never used with a non-zero shortAddr, and it's unspecified
		// what they would do with a non-zero shortAddr, so this is the best I've got

		this->setReg(d, this->memory[addr]);
	} break;

	case Opcode::ST: {
		int32_t data = this->getReg(i.cimmB());
		int32_t addr = this->getReg(i.cimmD());

		this->memory[addr] = data;
	} break;

	case Opcode::MOV: {
		// idk which reg is supposed to be moved so I'll just use s1...
		int32_t s1 = this->getReg(i.arithS1());
		this->setReg(i.arithD(), s1);
	} break;

	case Opcode::ADD: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 + s2);
	} break;

	case Opcode::SUB: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 - s2);
	} break;

	case Opcode::MUL: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 * s2);
	} break;

	case Opcode::DIV: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 / s2);
	} break;

	case Opcode::AND: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 & s2);
	} break;

	case Opcode::OR: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());
		this->setReg(i.arithD(), s1 | s2);
	} break;

	case Opcode::MOVI: {
		uint8_t b = i.cimmB();
		uint8_t d = i.cimmD();

		// if the d-reg is 0, the short addr (last 16 bits) contains data
		if (d == 0) {
			// which is moved into the b-reg? the spec isn't clear
			this->setReg(b, i.shortAddr());
		} else {
			this->setReg(d, this->memory[i.shortAddr() + d]);
		}
	} break;
			
	case Opcode::ADDI: {
		std::cout << "ADDI" << std::endl;
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) + i.shortAddr());
	} break;

	case Opcode::MULI: {
		std::cout << "MULI" << std::endl;
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) * i.shortAddr());
	} break;

	case Opcode::DIVI: {
		std::cout << "DIVI" << std::endl;
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) / i.shortAddr());
	} break;

	case Opcode::LDI: {

		std::cout << "LDI" << std::endl;
		int32_t b = this->getReg(i.get_val1());

		this->setReg(i.get_val3(), b);
	} break;

	case Opcode::SLT: {
		uint32_t s1 = this->getReg(i.arithS1());
		uint32_t s2 = this->getReg(i.arithS2());

		// ???
		uint32_t data1 = this->memory[s1];
		uint32_t data2 = this->memory[s2];

		if (data1 < data2) {
			this->setReg(i.arithD(), 1);
		} else {
			this->setReg(i.arithD(), 0);
		}
	} break;

	// ? hmmmmmm
	case Opcode::SLTI: {
		std::cout << "SLTI" << std::endl;
		int32_t s1 = this->getReg(i.cimmB());
		int32_t s2 = this->getReg(i.cimmD());

		if (data1 < data2) {
			this->setReg(i.cimmB(), 1);
		}
		else {
			this->setReg(i.cimmD(), 0);
		}
	} break;

	case Opcode::HLT: {
		std::cout << "HLT" << std::endl;
		// set process state to finished
		PCB_info pcb_val = ram1->get_info();
		pcb_val.pc.process_status = TERMINATE;
	} break;

	case Opcode::NOP:
		break;

	case Opcode::JMP: {
		this->pc = i.longAddr();
	} break;

	case Opcode::BEQ: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b == d) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BNE: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b != d) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BEZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b == 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BNZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b != 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BGZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b > 0) {
			this->pc = i.shortAddr();
		}
	} break;

	case Opcode::BLZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b < 0) {
			this->pc = i.shortAddr();
		}
	} break;

	default:
		std::cout << "unknown instruction" << std::endl;
		disassembleInstruction(i);
	}
}

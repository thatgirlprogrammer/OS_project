#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	// need to use actual memory
	for (uint32_t i = 0; i < MEMORY; i++)
		this->memory[i] = 0;

	this->memory[0] = 0xC050005C;
	this->memory[1] = 0x4B060000;
	this->memory[2] = 0x4B010000;
	this->memory[3] = 0x4B000000;
	this->memory[4] = 0x4F0A005C;
	this->memory[5] = 0x4F0D00DC;
	this->memory[6] = 0x4C0A0004;
	this->memory[7] = 0xC0BA0000;
	this->memory[8] = 0x42BD0000;
	this->memory[9] = 0x4C0D0004;
	this->memory[10] = 0x4C060001;
	this->memory[11] = 0x10658000;
	this->memory[12] = 0x56810018;
	this->memory[13] = 0x4B060000;
	this->memory[14] = 0x4F0900DC;
	this->memory[15] = 0x43970000;
	this->memory[16] = 0x05070000;
	this->memory[17] = 0x4C060001;
	this->memory[18] = 0x4C090004;
	this->memory[19] = 0x10658000;
	this->memory[20] = 0x5681003C;
	this->memory[21] = 0xC10000AC;
	this->memory[22] = 0x92000000;

	this->memory[0x5c] = 0x0000000A;
	this->memory[0x5d] = 0x00000006;
	this->memory[0x5e] = 0x0000002C;
	this->memory[0x5f] = 0x00000045;
	this->memory[0x60] = 0x00000001;
	this->memory[0x61] = 0x00000007;
	this->memory[0x62] = 0x00000000;
	this->memory[0x63] = 0x00000001;
	this->memory[0x64] = 0x00000005;
	this->memory[0x65] = 0x0000000A;
	this->memory[0x66] = 0x00000055;

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
	disassembleInstruction(i);

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
		uint32_t wrr1 = this->getReg(i.ioR1());
		uint8_t wrr2 = i.ioR2();
		uint32_t wraddr = i.shortAddr();

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
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) + i.shortAddr());
	} break;

	case Opcode::MULI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) * i.shortAddr());
	} break;

	case Opcode::DIVI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) / i.shortAddr());
	} break;

	case Opcode::LDI: {

		int32_t b = this->getReg(i.cimmB());

		this->setReg(i.cimmB(), b);
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
		int32_t s1 = this->getReg(i.cimmB());
		int32_t s2 = this->getReg(i.cimmD());

		if (s1 < s2) {
			this->setReg(i.cimmB(), 1);
		}
		else {
			this->setReg(i.cimmD(), 0);
		}
	} break;

	case Opcode::HLT: {
		// set process state to finished
		//PCB_info pcb_val = ram1->get_info();
		//pcb_val.pc.process_status = TERMINATE;
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
	//ram1->get_info().pc.program_counter++;
}

#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	// need to use actual memory
	for (uint32_t i = 0; i < MEMORY; i++)
		this->memory[i] = 0;

	/*
	// job 1
	this->setMem(0, 0xC050005C);
	this->setMem(1 * 4, 0x4B060000);
	this->setMem(2 * 4, 0x4B010000);
	this->setMem(3 * 4, 0x4B000000);
	this->setMem(4 * 4, 0x4F0A005C);
	this->setMem(5 * 4, 0x4F0D00DC);
	this->setMem(6 * 4, 0x4C0A0004);
	this->setMem(7 * 4, 0xC0BA0000);
	this->setMem(8 * 4, 0x42BD0000);
	this->setMem(9 * 4, 0x4C0D0004);
	this->setMem(10 * 4, 0x4C060001);
	this->setMem(11 * 4, 0x10658000);
	this->setMem(12 * 4, 0x56810018);
	this->setMem(13 * 4, 0x4B060000);
	this->setMem(14 * 4, 0x4F0900DC);
	this->setMem(15 * 4, 0x43970000);
	this->setMem(16 * 4, 0x05070000);
	this->setMem(17 * 4, 0x4C060001);
	this->setMem(18 * 4, 0x4C090004);
	this->setMem(19 * 4, 0x10658000);
	this->setMem(20 * 4, 0x5681003C);
	this->setMem(21 * 4, 0xC10000AC);
	this->setMem(22 * 4, 0x92000000);

	this->setMem(23 * 4, 0x0000000A);
	this->setMem(24 * 4, 0x00000006);
	this->setMem(25 * 4, 0x0000002C);
	this->setMem(26 * 4, 0x00000045);
	this->setMem(27 * 4, 0x00000001);
	this->setMem(28 * 4, 0x00000007);
	this->setMem(29 * 4, 0x00000000);
	this->setMem(30 * 4, 0x00000001);
	this->setMem(31 * 4, 0x00000005);
	this->setMem(32 * 4, 0x0000000A);
	this->setMem(33 * 4, 0x00000055);
	// */

	///*
	// job 2
	this->setMem(0 * 4, 0xC0500070);
	this->setMem(1 * 4, 0x4B060000);
	this->setMem(2 * 4, 0x4B010000);
	this->setMem(3 * 4, 0x4B000000);
	this->setMem(4 * 4, 0x4F0A0070);
	this->setMem(5 * 4, 0x4F0D00F0);
	this->setMem(6 * 4, 0x4C0A0004);
	this->setMem(7 * 4, 0xC0BA0000);
	this->setMem(8 * 4, 0x42BD0000);
	this->setMem(9 * 4, 0x4C0D0004);
	this->setMem(10 * 4, 0x4C060001);
	this->setMem(11 * 4, 0x10658000);
	this->setMem(12 * 4, 0x56810018);
	this->setMem(13 * 4, 0x4B060000);
	this->setMem(14 * 4, 0x4F0900F0);
	this->setMem(15 * 4, 0x43900000);
	this->setMem(16 * 4, 0x4C060001);
	this->setMem(17 * 4, 0x4C090004);
	this->setMem(18 * 4, 0x43920000);
	this->setMem(19 * 4, 0x4C060001);
	this->setMem(20 * 4, 0x4C090004);
	this->setMem(21 * 4, 0x10028000);
	this->setMem(22 * 4, 0x55810060);
	this->setMem(23 * 4, 0x04020000);
	this->setMem(24 * 4, 0x10658000);
	this->setMem(25 * 4, 0x56810048);
	this->setMem(26 * 4, 0xC10000C0);
	this->setMem(27 * 4, 0x92000000);

	this->setMem(28 * 4, 0x0000000A);
	this->setMem(29 * 4, 0x00000006);
	this->setMem(30 * 4, 0x0000002C);
	this->setMem(31 * 4, 0x00000045);
	this->setMem(32 * 4, 0x00000001);
	this->setMem(33 * 4, 0x00000007);
	this->setMem(34 * 4, 0x00000000);
	this->setMem(35 * 4, 0x00000001);
	this->setMem(36 * 4, 0x00000005);
	this->setMem(37 * 4, 0x0000000A);
	this->setMem(38 * 4, 0x00000055);
	// */

	/*
	// program C
	this->setMem(0 * 4, 0xC0500070);
	this->setMem(1 * 4, 0x4B060000);
	this->setMem(2 * 4, 0x4B010000);
	this->setMem(3 * 4, 0x4B000000);
	this->setMem(4 * 4, 0x4F0A0070);
	this->setMem(5 * 4, 0x4F0D00F0);
	this->setMem(6 * 4, 0x4C0A0004);
	this->setMem(7 * 4, 0xC0BA0000);
	this->setMem(8 * 4, 0x42BD0000);
	this->setMem(9 * 4, 0x4C0D0004);
	this->setMem(10 * 4, 0x4C060001);
	this->setMem(11 * 4, 0x10658000);
	this->setMem(12 * 4, 0x56810018);
	this->setMem(13 * 4, 0x4B060000);
	this->setMem(14 * 4, 0x4F0900F0);
	this->setMem(15 * 4, 0x43900000);
	this->setMem(16 * 4, 0x4C060001);
	this->setMem(17 * 4, 0x4C090004);
	this->setMem(18 * 4, 0x43920000);
	this->setMem(19 * 4, 0x4C060001);
	this->setMem(20 * 4, 0x4C090004);
	this->setMem(21 * 4, 0x10028000);
	this->setMem(22 * 4, 0x55810060);
	this->setMem(23 * 4, 0x04020000);
	this->setMem(24 * 4, 0x10658000);
	this->setMem(25 * 4, 0x56810048);
	this->setMem(26 * 4, 0xC10000C0);
	this->setMem(27 * 4, 0x92000000);

	this->setMem(28 * 4, 0x0000000A);
	this->setMem(29 * 4, 0x00000006);
	this->setMem(30 * 4, 0x0000002C);
	this->setMem(31 * 4, 0x00000045);
	this->setMem(32 * 4, 0x000000E1);
	this->setMem(33 * 4, 0x00000017);
	this->setMem(34 * 4, 0x00000000);
	this->setMem(35 * 4, 0x00000002);
	this->setMem(36 * 4, 0x00000005);
	this->setMem(37 * 4, 0x000000AA);
	this->setMem(38 * 4, 0x00000055);
	/**/

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

int32_t CPU::getMem(uint16_t addr) {
	int32_t result = this->memory[addr] << 24;
	result |= this->memory[addr + 1] << 16;
	result |= this->memory[addr + 2] << 8;
	result |= this->memory[addr + 3];
	return result;
}

void CPU::setMem(uint16_t addr, int32_t data) {
	this->memory[addr] = data >> 24;
	this->memory[addr + 1] = data >> 16;
	this->memory[addr + 2] = data >> 8;
	this->memory[addr + 3] = data;
}

void CPU::step() {
	// get program counter from PCB
	// TODO: offset
	std::cout << std::hex << this->pc << std::dec << " ";
	Instruction i = Instruction(this->getMem(this->pc));
	this->pc += 4;
	disassembleInstruction(i);

	switch (i.opcode()) {
	case Opcode::RD: {
		uint8_t r1 = i.ioR1();
		int32_t r2 = this->getReg(i.ioR2());
		uint32_t rdaddr = i.shortAddr();

		// assuming the same rules as immediate instructions, if r2 is 0,
		// read from the address instead of the register
		int32_t data;
		if (rdaddr == 0) {
			data = this->getMem(r2);
		} else {
			data = this->getMem(rdaddr);
		}

		this->setReg(r1, data);
	} break;

	case Opcode::WR: {
		uint32_t wrr1 = this->getReg(i.ioR1());
		uint32_t wrr2 = this->getReg(i.ioR2());
		uint32_t wraddr = i.shortAddr();

		if (wraddr == 0) {
			this->setMem(wrr2, wrr1);
		} else {
			this->setMem(wraddr, wrr1);
		}
	} break;

	case Opcode::LW: {
		int32_t addr = this->getReg(i.cimmB());
		uint32_t d = i.cimmD();

		// LW and ST are never used with a non-zero shortAddr, and it's unspecified
		// what they would do with a non-zero shortAddr, so this is the best I've got

		this->setReg(d, this->getMem(addr));
	} break;

	case Opcode::ST: {
		int32_t data = this->getReg(i.cimmB());
		int32_t addr = this->getReg(i.cimmD());

		this->setMem(addr, data);
	} break;

	case Opcode::MOV: {
		int32_t d = this->getReg(i.arithS2());
		this->setReg(i.arithS1(), d);
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
		uint8_t d = i.cimmD();
		this->setReg(d, i.shortAddr());
	} break;
			
	case Opcode::ADDI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) + i.shortAddr());
	} break;

	case Opcode::MULI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) * (i.shortAddr()));
	} break;

	case Opcode::DIVI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) / i.shortAddr());
	} break;

	case Opcode::LDI: {
		this->setReg(i.cimmD(), i.shortAddr());
	} break;

	case Opcode::SLT: {
		int32_t s1 = this->getReg(i.arithS1());
		int32_t s2 = this->getReg(i.arithS2());

		if (s1 < s2) {
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
		} else {
			this->setReg(i.cimmD(), 0);
		}
	} break;

	case Opcode::HLT: {
		// set process state to finished
		//PCB_info pcb_val = ram1->get_info();
		//pcb_val.pc.process_status = TERMINATE;
		this->done = true;
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

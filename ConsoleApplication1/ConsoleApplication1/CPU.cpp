#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU() {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	// need to use actual memory
	for (uint32_t i = 0; i < MEMORY; i++)
		this->memory[i] = 0;
	/* Program 1
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
	this->memory[23] = 0x0000000A;
	this->memory[24] = 0x00000006;
	this->memory[25] = 0x0000002C;
	this->memory[26] = 0x00000045;
	this->memory[27] = 0x00000001;
	this->memory[28] = 0x00000007;
	this->memory[29] = 0x00000000;
	this->memory[30] = 0x00000001;
	this->memory[31] = 0x00000005;
	this->memory[32] = 0x0000000A;
	this->memory[33] = 0x00000055;*/
/* Program 2*/
		this->memory[0] = 0xC0500070;
		this->memory[1] = 0x4B060000;
		this->memory[2] = 0x4B010000;
		this->memory[3] = 0x4B000000;
		this->memory[4] = 0x4F0A0070;
		this->memory[5] = 0x4F0D00F0;
		this->memory[6] = 0x4C0A0004;
		this->memory[7] = 0xC0BA0000;
		this->memory[8] = 0x42BD0000;
		this->memory[9] = 0x4C0D0004;
		this->memory[10] = 0x4C060001;
		this->memory[11] = 0x10658000;
		this->memory[12] = 0x56810018;
		this->memory[13] = 0x4B060000;
		this->memory[14] = 0x4F0900F0;
		this->memory[15] = 0x43900000;
		this->memory[16] = 0x4C060001;
		this->memory[17] = 0x4C090004;
		this->memory[18] = 0x43920000;
		this->memory[19] = 0x4C060001;
		this->memory[20] = 0x4C090004;
		this->memory[21] = 0x10028000;
		this->memory[22] = 0x55810060;
		this->memory[23] = 0x04020000;
		this->memory[24] = 0x10658000;
		this->memory[25] = 0x56810048;
		this->memory[26] = 0xC10000C0;
		this->memory[27] = 0x92000000;

		this->memory[28] = 0x0000000A;
		this->memory[29] = 0x00000006;
		this->memory[30] = 0x0000002C;
		this->memory[31] = 0x00000045;
		this->memory[32] = 0x00000001;
		this->memory[33] = 0x00000007;
		this->memory[34] = 0x00000000;
		this->memory[35] = 0x00000001;
		this->memory[36] = 0x00000005;
		this->memory[37] = 0x0000000A;
		this->memory[38] = 0x00000055;
		this->memory[39] = 0x00000000;
		this->memory[40] = 0x00000000;
		this->memory[41] = 0x00000000;
		this->memory[42] = 0x00000000;
		this->memory[43] = 0x00000000;
		this->memory[44] = 0x00000000;
		this->memory[45] = 0x00000000;
		this->memory[46] = 0x00000000;
		this->memory[47] = 0x00000000;
		this->memory[48] = 0x00000000;
		this->memory[49] = 0x00000000;
		this->memory[50] = 0x00000000;
		this->memory[51] = 0x00000000;
		this->memory[52] = 0x00000000;
		this->memory[53] = 0x00000000;
		this->memory[54] = 0x00000000;
		this->memory[55] = 0x00000000;
		this->memory[56] = 0x00000000;
		this->memory[57] = 0x00000000;
		this->memory[58] = 0x00000000;
		this->memory[59] = 0x00000000;
		this->memory[60] = 0x00000000;
		this->memory[61] = 0x00000000;
		this->memory[62] = 0x00000000;
		this->memory[63] = 0x00000000;
		this->memory[64] = 0x00000000;
		this->memory[65] = 0x00000000;
		this->memory[66] = 0x00000000;
		this->memory[67] = 0x00000000;
		this->memory[68] = 0x00000000;
		this->memory[69] = 0x00000000;
		this->memory[70] = 0x00000000;
		this->memory[71] = 0x00000000;

/* Program 3
this->memory[0] = 0xC0500060;
this->memory[1] = 0x4B060000;
this->memory[2] = 0x4B010000;
this->memory[3] = 0x4B000000;
this->memory[4] = 0x4F0A0060;
this->memory[5] = 0x4F0D00E0;
this->memory[6] = 0x4C0A0004;
this->memory[7] = 0xC0BA0000;
this->memory[8] = 0x42BD0000;
this->memory[9] = 0x4C0D0004;
this->memory[10] = 0x4C060001;
this->memory[11] = 0x10658000;
this->memory[12] = 0x56810018;
this->memory[13] = 0x4B060000;
this->memory[14] = 0x4F0900E0;
this->memory[15] = 0x43970000;
this->memory[16] = 0x05070000;
this->memory[17] = 0x4C060001;
this->memory[18] = 0x4C090004;
this->memory[19] = 0x10658000;
this->memory[20] = 0x5681003C;
this->memory[21] = 0x08050000;
this->memory[22] = 0xC10000B0;
this->memory[23] = 0x92000000;

this->memory[24] = 0x0000000A;
this->memory[25] = 0x00000006;
this->memory[26] = 0x0000002C;
this->memory[27] = 0x00000045;
this->memory[28] = 0x00000001;
this->memory[29] = 0x00000009;
this->memory[30] = 0x000000B0;
this->memory[31] = 0x00000001;
this->memory[32] = 0x00000007;
this->memory[33] = 0x000000AA;
this->memory[34] = 0x00000055;
this->memory[35] = 0x00000000;
this->memory[36] = 0x00000000;
this->memory[37] = 0x00000000;
this->memory[37] = 0x00000000;
this->memory[39] = 0x00000000;
this->memory[40] = 0x00000000;
this->memory[41] = 0x00000000;
this->memory[42] = 0x00000000;
this->memory[43] = 0x00000000;
this->memory[44] = 0x00000000;
this->memory[45] = 0x00000000;
this->memory[46] = 0x00000000;
this->memory[47] = 0x00000000;
this->memory[48] = 0x00000000;
this->memory[49] = 0x00000000;
this->memory[50] = 0x00000000;
this->memory[51] = 0x00000000;
this->memory[52] = 0x00000000;
this->memory[53] = 0x00000000;
this->memory[54] = 0x00000000;
this->memory[55] = 0x00000000;
this->memory[56] = 0x00000000;
this->memory[57] = 0x00000000;
this->memory[58] = 0x00000000;
this->memory[59] = 0x00000000;
this->memory[60] = 0x00000000;
this->memory[61] = 0x00000000;
this->memory[62] = 0x00000000;
this->memory[63] = 0x00000000;
this->memory[64] = 0x00000000;
this->memory[65] = 0x00000000;
this->memory[66] = 0x00000000;
this->memory[67] = 0x00000000;*/

/* Program 4
this->memory[0] = 0xC050004C;
this->memory[1] = 0x4B060000;
this->memory[2] = 0x4B000000;
this->memory[3] = 0x4B010000;
this->memory[4] = 0x4B020000;
this->memory[5] = 0x4B030001;
this->memory[6] = 0x4F07009C;
this->memory[7] = 0xC1270000;
this->memory[8] = 0x4C070004;
this->memory[9] = 0x4C060001;
this->memory[10] = 0x05320000;
this->memory[11] = 0xC1070000;
this->memory[12] = 0x4C070004;
this->memory[13] = 0x4C060001;
this->memory[14] = 0x04230000;
this->memory[15] = 0x04300000;
this->memory[16] = 0x10658000;
this->memory[17] = 0x56810028;
this->memory[18] = 0x92000000;

this->memory[19] = 0x0000000B;
this->memory[20] = 0x00000000;
this->memory[21] = 0x00000000;
this->memory[22] = 0x00000000;
this->memory[23] = 0x00000000;
this->memory[24] = 0x00000000;
this->memory[25] = 0x00000000;
this->memory[26] = 0x00000000;
this->memory[27] = 0x00000000;
this->memory[28] = 0x00000000;
this->memory[29] = 0x00000000;
this->memory[30] = 0x00000000;
this->memory[31] = 0x00000000;
this->memory[32] = 0x00000000;
this->memory[33] = 0x00000000;
this->memory[34] = 0x00000000;
this->memory[35] = 0x00000000;
this->memory[36] = 0x00000000;
this->memory[37] = 0x00000000;
this->memory[38] = 0x00000000;
this->memory[39] = 0x00000000;
this->memory[40] = 0x00000000;
this->memory[41] = 0x00000000;
this->memory[42] = 0x00000000;
this->memory[43] = 0x00000000;
this->memory[44] = 0x00000000;
this->memory[45] = 0x00000000;
this->memory[46] = 0x00000000;
this->memory[47] = 0x00000000;
this->memory[48] = 0x00000000;
this->memory[49] = 0x00000000;
this->memory[50] = 0x00000000;
this->memory[51] = 0x00000000;
this->memory[52] = 0x00000000;
this->memory[53] = 0x00000000;
this->memory[54] = 0x00000000;
this->memory[55] = 0x00000000;
this->memory[56] = 0x00000000;
this->memory[57] = 0x00000000;
this->memory[58] = 0x00000000;
this->memory[59] = 0x00000000;
this->memory[60] = 0x00000000;
this->memory[61] = 0x00000000;
this->memory[62] = 0x00000000;*/


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
	/*
	this->pc = 0;
	this->memory[0] = 0xC0500060;
this->memory[1] = 0x4B060000;
this->memory[2] = 0x4B010000;
this->memory[3] = 0x4B000000;
this->memory[4] = 0x4F0A0060;
this->memory[5] = 0x4F0D00E0;
this->memory[6] = 0x4C0A0004;
this->memory[7] = 0xC0BA0000;
this->memory[8] = 0x42BD0000;
this->memory[9] = 0x4C0D0004;
this->memory[10] = 0x4C060001;
this->memory[11] = 0x10658000;
this->memory[12] = 0x56810018;
this->memory[13] = 0x4B060000;
this->memory[14] = 0x4F0900E0;
this->memory[15] = 0x43970000;
this->memory[16] = 0x05070000;
this->memory[17] = 0x4C060001;
this->memory[18] = 0x4C090004;
this->memory[19] = 0x10658000;
this->memory[20] = 0x5681003C;
this->memory[21] = 0x08050000;
this->memory[22] = 0xC10000B0;
this->memory[23] = 0x92000000;

this->memory[24] = 0x0000000A;
this->memory[25] = 0x00000006;
this->memory[26] = 0x0000002C;
this->memory[27] = 0x00000045;
this->memory[28] = 0x00000001;
this->memory[29] = 0x00000009;
this->memory[30] = 0x000000B0;
this->memory[31] = 0x00000001;
this->memory[32] = 0x00000007;
this->memory[33] = 0x000000AA;
this->memory[34] = 0x00000055;
this->memory[35] = 0x00000000;
this->memory[36] = 0x00000000;
this->memory[37] = 0x00000000;
this->memory[37] = 0x00000000;
this->memory[39] = 0x00000000;
this->memory[40] = 0x00000000;
this->memory[41] = 0x00000000;
this->memory[42] = 0x00000000;
this->memory[43] = 0x00000000;
this->memory[44] = 0x00000000;
this->memory[45] = 0x00000000;
this->memory[46] = 0x00000000;
this->memory[47] = 0x00000000;
this->memory[48] = 0x00000000;
this->memory[49] = 0x00000000;
this->memory[50] = 0x00000000;
this->memory[51] = 0x00000000;
this->memory[52] = 0x00000000;
this->memory[53] = 0x00000000;
this->memory[54] = 0x00000000;
this->memory[55] = 0x00000000;
this->memory[56] = 0x00000000;
this->memory[57] = 0x00000000;
this->memory[58] = 0x00000000;
this->memory[59] = 0x00000000;
this->memory[60] = 0x00000000;
this->memory[61] = 0x00000000;
this->memory[62] = 0x00000000;
this->memory[63] = 0x00000000;
this->memory[64] = 0x00000000;
this->memory[65] = 0x00000000;
this->memory[66] = 0x00000000;
this->memory[67] = 0x00000000;*/
		//this->pc = 0;
	// get program counter from PCB
	// TODO: offset
	Instruction i = Instruction(this->memory[this->pc++]);
	disassembleInstruction(i);

	switch (i.opcode()) {
	case Opcode::RD: {
		uint8_t r1 = i.ioR1();
		int32_t r2 = this->getReg(i.ioR2());
		uint32_t rdaddr = i.shortAddr() / 4;

		// assuming the same rules as immediate instructions, if r2 is 0,
		// read from the address instead of the register
		int32_t data;
		if (rdaddr == 0) {
			data = this->memory[r2];
		} else {
			data = this->memory[rdaddr];
		}

		this->setReg(r1, data);
	} break;

	case Opcode::WR: {
		std::cout << "WR" << std::endl;
		uint32_t wrr1 = this->getReg(i.ioR1());
		uint32_t wrr2 = this->getReg(i.ioR2());
		uint32_t wraddr = i.shortAddr() / 4;

		//if (wrr2 > 0) {
		//	this->setReg(wrr2, wrr1);
		//}
		//else {
		if (wraddr == 0) {
			memory[wrr2] = wrr1;
		}
		else {
			memory[wraddr] = wrr1;
		}
	//	}
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
		//int32_t s1 = this->getReg(i.arithS1());
		//this->setReg(i.arithD(), s1);
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
		//uint8_t b = i.cimmB();
		uint8_t d = i.cimmD();
		if (i.shortAddr() < 0x4) {
			this->setReg(d, i.shortAddr() % 4);
		}
		else {
			this->setReg(d, i.shortAddr() / 4);
		}	

		//// if the d-reg is 0, the short addr (last 16 bits) contains data
		//if (d == 0) {
		//	// which is moved into the b-reg? the spec isn't clear
		//	this->setReg(b, i.shortAddr());
		//} else {
		//	this->setReg(d, this->memory[i.shortAddr() + d]);
		//}
	} break;
			
	case Opcode::ADDI: {
		uint8_t d = i.cimmD();
		if (i.shortAddr() < 4) {
			this->setReg(d, this->getReg(d) + (i.shortAddr() % 4));
		}
		else {
			this->setReg(d, this->getReg(d) + (i.shortAddr() / 4));
		}
		
	} break;

	case Opcode::MULI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) * (i.shortAddr()));
	} break;

	case Opcode::DIVI: {
		uint8_t d = i.cimmD();
		this->setReg(d, this->getReg(d) / (i.shortAddr() / 4));
	} break;

	case Opcode::LDI: {
		this->setReg(i.cimmD(), i.shortAddr() / 4);

		//int32_t b = this->getReg(i.cimmB());
		//this->setReg(i.cimmB(), b);
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
		this->pc = i.longAddr() / 4;
	} break;

	case Opcode::BEQ: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b == d) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	case Opcode::BNE: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b != d) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	case Opcode::BEZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b == 0) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	case Opcode::BNZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b != 0) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	case Opcode::BGZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b > 0) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	case Opcode::BLZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b < 0) {
			this->pc = i.shortAddr() / 4;
		}
	} break;

	default:
		std::cout << "unknown instruction" << std::endl;
		disassembleInstruction(i);
	}
	//ram1->get_info().pc.program_counter++;
}

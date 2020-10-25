#include <iostream>
#include "CPU.h"
#include "Disassemble.h"

OSSim::CPU::CPU() {
	ram1 = new ram();
	this->instructions = instructions;
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	for (uint32_t i = 0; i < MEMORY; i++)
		this->memory[i] = 0;
	this->pc = 0;

}

void OSSim::CPU::load_into_ram(vector<Instruction>* val, PCB_info pcb)
{
	//ram1->store(val, pcb);
	this->instructions = disassemble(*val);
}

int32_t OSSim::CPU::getReg(uint8_t reg) {
	if (reg == 1) {
		return 0;
	} else {
		return this->registers[reg];
	}
}

void OSSim::CPU::setReg(uint8_t reg, int32_t value) {
	this->registers[reg] = value;
}

void OSSim::CPU::step() {
	for (int j = 0; j < instructions.size(); j++) {
		disassemabled_instructions i = instructions.at(j);

		switch (i.get_opcode()) {
		case Opcode::RD: {
			std::cout << "RD" << std::endl;
			uint8_t r1 = i.get_val1();
			int32_t r2 = this->getReg(i.get_val2());
			uint32_t rdaddr = i.get_val3();

			// assuming the same rules as immediate instructions, if r2 is 0,
			// read from the address instead of the register
			int32_t data;
			if (r2 == 0) {
				data = this->memory[rdaddr];
			}
			else {
				data = this->memory[r2];
			}

			this->setReg(r1, data);
		} break;

		case Opcode::WR: {
			std::cout << "WR" << std::endl;
			int32_t wrr1 = this->getReg(i.get_val1());
			// good luck luke xd
		} break;

		case Opcode::LW: {
			std::cout << "LW" << std::endl;
			int32_t addr = this->getReg(i.get_val1());
			uint32_t d = i.get_val2();

			// LW and ST are never used with a non-zero shortAddr, and it's unspecified
			// what they would do with a non-zero shortAddr, so this is the best I've got

			this->setReg(d, this->memory[addr]);
		} break;

		case Opcode::ST: {
			std::cout << "ST" << std::endl;
			int32_t data = this->getReg(i.get_val1());
			int32_t addr = this->getReg(i.get_val2());

			this->memory[addr] = data;
		} break;

		case Opcode::MOV: {
			std::cout << "MOV" << std::endl;
			// idk which reg is supposed to be moved so I'll just use s1...
			int32_t s1 = this->getReg(i.get_val1());
			this->setReg(i.get_val3(), s1);
		} break;

		case Opcode::ADD: {
			std::cout << "ADD" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 + s2);
		} break;

		case Opcode::SUB: {
			std::cout << "SUB" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 - s2);
		} break;

		case Opcode::MUL: {
			std::cout << "MUL" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 * s2);
		} break;

		case Opcode::DIV: {
			std::cout << "DIV" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 / s2);
		} break;

		case Opcode::AND: {
			std::cout << "AND" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 & s2);
		} break;

		case Opcode::OR: {
			std::cout << "OR" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());
			this->setReg(i.get_val3(), s1 | s2);
		} break;

		case Opcode::MOVI: {
			std::cout << "MOVI" << std::endl;
			uint32_t b = i.get_val1();
			uint32_t d = i.get_val2();

			// if the d-reg is 0, the short addr (last 16 bits) contains data
			if (d == 0) {
				// which is moved into the b-reg? the spec isn't clear
				this->setReg(b, i.get_val3());
			}
			else {
				this->setReg(d, this->memory[i.get_val3() + d]);
			}
		} break;

			// addi muli divi ldi

		case Opcode::SLT: {
			std::cout << "SLT" << std::endl;
			int32_t s1 = this->getReg(i.get_val1());
			int32_t s2 = this->getReg(i.get_val2());

			// ???
			uint32_t data1 = this->memory[s1];
			uint32_t data2 = this->memory[s2];

			if (data1 < data2) {
				this->setReg(i.get_val1(), 1);
			}
			else {
				this->setReg(i.get_val2(), 0);
			}
		} break;

			// slti

		case Opcode::HLT: {
			std::cout << "HLT" << std::endl;
			// set process state to finished
		} break;

		case Opcode::NOP: {
			std::cout << "NOP" << std::endl;
		} break;

		case Opcode::JMP: {
			std::cout << "JMP" << std::endl;
			this->pc = i.get_val1();
		} break;

		case Opcode::BEQ: {
			std::cout << "BEQ" << std::endl;
			int32_t b = this->getReg(i.get_val1());
			int32_t d = this->getReg(i.get_val2());

			if (b == d) {
				this->pc = i.get_val3();
			}
		} break;

		case Opcode::BNE: {
			std::cout << "BNE" << std::endl;
			int32_t b = this->getReg(i.get_val1());
			int32_t d = this->getReg(i.get_val2());

			if (b != d) {
				this->pc = i.get_val3();
			}
		} break;

		case Opcode::BEZ: {
			std::cout << "BEZ" << std::endl;
			int32_t b = this->getReg(i.get_val1());

			if (b == 0) {
				this->pc = i.get_val3();
			}
		} break;

		case Opcode::BNZ: {
			std::cout << "BNZ" << std::endl;
			int32_t b = this->getReg(i.get_val1());

			if (b != 0) {
				this->pc = i.get_val3();
			}
		} break;

		case Opcode::BGZ: {
			std::cout << "BGZ" << std::endl;
			int32_t b = this->getReg(i.get_val2());

			if (b > 0) {
				this->pc = i.get_val3();
			}
		} break;

		case Opcode::BLZ: {
			std::cout << "BLZ" << std::endl;
			int32_t b = this->getReg(i.get_val1());

			if (b < 0) {
				this->pc = i.get_val3();
			}
		} break;
		case Opcode::LDI: {
			//TODO
			std::cout << "LDI" << std::endl;
		} break;
		case Opcode::ADDI: {
			//TODO
			std::cout << "ADDI" << std::endl;
		} break;
		default:
			std::cout << "unknown instruction" << std::endl;
			//disassembleInstruction(i);
		}
	}
}

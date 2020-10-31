#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU(Memory* memory, DMA* dma) {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	this->memory = memory;
	this->dma = dma;
	this->pc = 0;
	this->base = 0;
}

int32_t CPU::getReg(uint8_t reg) {
	if (reg == 1) {
		return 0;
	}
	else {
		return this->registers[reg];
	}
}

void CPU::setReg(uint8_t reg, int32_t value) {
	this->registers[reg] = value;
}

void CPU::step() {
	// TODO: get program counter from PCB
	std::cout << std::hex << this->pc << std::dec << " ";
	Instruction i = Instruction(this->memory->getMem(this->pc));
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
			if (use_cache) {
				data = readCache(r2);
			}
			else {
				data = this->dma->read(r2 + (this->base * 4));
			}
			//data = this->memory->getMem(r2 + (this->base * 4));
			std::cout << r2 + (this->base * 4) << std::endl;
		}
		else {
			if (use_cache) {
				data = readCache(rdaddr);
			}
			else {
				data = this->dma->read(rdaddr + (this->base * 4));
			}
			//data = this->memory->getMem(rdaddr + (this->base * 4));
			std::cout << rdaddr + (this->base * 4) << std::endl;
		}

		this->setReg(r1, data);
	} break;

	case Opcode::WR: {
		uint32_t wrr1 = this->getReg(i.ioR1());
		uint32_t wrr2 = this->getReg(i.ioR2());
		uint32_t wraddr = i.shortAddr();

		if (wraddr == 0) {
			if (use_cache) {
				writeCache(wrr2, wrr1);
			}
			else {
				this->dma->write(wrr2 + (this->base * 4), wrr1);
			}
			//this->memory->setMem(wrr2 + (this->base * 4), wrr1);
			std::cout << wrr2 + (this->base * 4) << std::endl;
		}
		else {
			if (use_cache) {
				writeCache(wraddr, wrr1);
			}
			else {
				this->dma->write(wraddr + (this->base * 4), wrr1);
			}
			//this->memory->setMem(wraddr + (this->base * 4), wrr1);
			std::cout << wraddr + (this->base * 4) << std::endl;
		}
	} break;

	case Opcode::LW: {
		int32_t addr = this->getReg(i.cimmB());
		uint32_t d = i.cimmD();

		// LW and ST are never used with a non-zero shortAddr, and it's unspecified
		// what they would do with a non-zero shortAddr, so this is the best I've got
		if (use_cache) {
			setReg(d, readCache(addr));
		}
		else {
			this->setReg(d, this->dma->read(addr + (this->base * 4)));
		}
	//	this->setReg(d, this->memory->getMem(addr + (this->base * 4)));
		std::cout << addr + (this->base * 4) << std::endl;
	} break;

	case Opcode::ST: {
		int32_t data = this->getReg(i.cimmB());
		int32_t addr = this->getReg(i.cimmD());

		if (use_cache) {
			writeCache(addr, data);
		}
		else {
			this->dma->write(addr + (this->base * 4), data);
		}
		
		//this->memory->setMem(addr + (this->base * 4), data);
		std::cout << addr + (this->base * 4) << std::endl;
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
		}
		else {
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
		if (use_cache) {
			PCB_info* process = private_running->at(0);
			uint16_t b = process->pc.job_memory_address;
			std::cout << "My b is " << b << std::endl;
			std::cout << "This is job " << process->pc.job_number << endl;
			auto size = process->pc.job_size;
			for (int i = 0; i < size * 4; i += 4) {
				dma->write((i + (b * 4)), readCache(i));
			}
			private_running->erase(private_running->begin() + 0);
		}
		this->done = true;
	} break;

	case Opcode::NOP:
		break;

	case Opcode::JMP: {
		this->pc = i.longAddr() + (this->base * 4);
	} break;

	case Opcode::BEQ: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b == d) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	case Opcode::BNE: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b != d) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	case Opcode::BEZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b == 0) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	case Opcode::BNZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b != 0) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	case Opcode::BGZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b > 0) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	case Opcode::BLZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b < 0) {
			this->pc = i.shortAddr() + (this->base * 4);
		}
	} break;

	default:
		std::cout << "unknown instruction" << std::endl;
		disassembleInstruction(i);
	}
	//ram1->get_info().pc.program_counter++;
}

uint32_t CPU::readCache(uint16_t addr) {
	assert(addr % 4 == 0);

	// TODO: get offset from PCB
	int32_t result = cache[addr] << 24;
	result |= cache[addr + 1] << 16;
	result |= cache[addr + 2] << 8;
	result |= cache[addr + 3];
	return result;
}

void CPU::writeCache(uint16_t addr, int32_t data) {
	assert(addr % 4 == 0);

	// TODO: get offset from PCB
	cache[addr] = data >> 24;
	cache[addr + 1] = data >> 16;
	cache[addr + 2] = data >> 8;
	cache[addr + 3] = data;
}

void CPU::appendRunning(PCB_info* pcb) {
	private_running->push_back(pcb);
}
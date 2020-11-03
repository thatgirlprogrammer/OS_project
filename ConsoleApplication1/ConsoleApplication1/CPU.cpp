#include <iostream>

#include "CPU.h"
#include "Disassemble.h"

CPU::CPU(Memory* memory, DMA* dma, int num, loader* l) {
	for (uint8_t i = 0; i < REGISTER_COUNT; i++)
		this->registers[i] = 0;
	this->memory = memory;
	this->dma = dma;
	this->pc = 0;
	this->base = 0;
	this->cpu_num = num;
	this->load = l;
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
	Instruction i = Instruction(0x13000000);
	if (use_cache) {
		i = Instruction(this->readCache(this->pc - this->base * 4));
	}
	else {
		i = Instruction(this->memory->getMem(this->pc));
	}
	this->pc += 4;
//	disassembleInstruction(i);

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
		}
		else {
			if (use_cache) {
				data = readCache(rdaddr);
			}
			else {
				data = this->dma->read(rdaddr + (this->base * 4));
			}
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
		}
		else {
			if (use_cache) {
				writeCache(wraddr, wrr1);
			}
			else {
				this->dma->write(wraddr + (this->base * 4), wrr1);
			}
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
		if (use_cache) {
			uint16_t b = this->running->pc.job_memory_address;
			auto size = this->running->pc.job_size;
			for (int i = 0; i < size * 4; i += 4) {
				this->dma->write((i + (b * 4)), readCache(i));
			}
		}

		this->running->total_memory_in_use = memory->in_use;

		for (int i = 0; i < (this->running->pc.job_size) * 4; i += 4) {
			memory->deallocate(i + (running->pc.job_memory_address * 4));
		}

		this->running->pc.process_status = TERMINATE;
		this->running->ios = dma->get_io_number();
		++num_processes;
		running->end = std::chrono::high_resolution_clock::now();
		load->get_terminated()->push_back(running);

		for (int i = 0; i < load->get_running()->size(); ++i) {
			if (load->get_running()->at(i) == this->running) {
				load->get_running()->erase(load->get_running()->begin() + i);
			}
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
		disassembleInstruction(i);
	}
}

uint32_t CPU::readCache(uint16_t addr) {
	assert(addr % 4 == 0);
	int32_t result = cache[addr] << 24;
	result |= cache[addr + 1] << 16;
	result |= cache[addr + 2] << 8;
	result |= cache[addr + 3];
	return result;
}

void CPU::writeCache(uint16_t addr, int32_t data) {
	assert(addr % 4 == 0);
	cache[addr] = data >> 24;
	cache[addr + 1] = data >> 16;
	cache[addr + 2] = data >> 8;
	cache[addr + 3] = data;
}

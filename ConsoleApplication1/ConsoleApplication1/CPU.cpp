#include <iostream>

#include "CPU.h"
#include "Disassemble.h"
#include <iostream>
#include <iomanip>

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
	std::cout << endl << running->pc.job_number << " running ";
	if (load->on_terminate(running)) {
		done = true;
		return;
	}
	Instruction i = Instruction(0x13000000);
	if (use_cache) {
		if (readCache(this->pc) == -1) {
			return;
		}
		i = Instruction(this->readCache(this->pc));
	}
	else {
//		i = Instruction(this->memory->getMem(this->pc));
	}
	this->pc += 4;
	disassembleInstruction(i);

	switch (i.opcode()) {
	case Opcode::RD: {
		if (running->pc.process_status == WAIT) {
			running->pc.process_status = RUN;
		}
		else {
			// trigger interrupt
			writePCBCache();
			done = true;
			load->move_waiting(running);
			return;
		}
		uint8_t r1 = i.ioR1();
		int32_t r2 = this->getReg(i.ioR2());
		uint32_t rdaddr = i.shortAddr();

		// assuming the same rules as immediate instructions, if r2 is 0,
		// read from the address instead of the register
		int32_t data;
		if (rdaddr == 0) {
			if (use_cache) {
				if (readCache(r2) == -1) {
					return;
				}
				data = readCache(r2);
				if (data == -1) {
					return;
				}
			}
			else {
		//		data = this->dma->read(r2 + (this->base * 4));
			}
		}
		else {
			if (use_cache) {
				data = readCache(rdaddr);
				if (data == -1) {
					return;
				}
			}
			else {
		//		data = this->dma->read(rdaddr + (this->base * 4));
			}
		}

		this->setReg(r1, data);
	} break;

	case Opcode::WR: {
		
		if (running->pc.process_status == WAIT) {
			running->pc.process_status = RUN;
		}
		else {
			// trigger interrupt
			writePCBCache();
			done = true;
			load->move_waiting(running);
			
			return;
		}
		uint32_t wrr1 = this->getReg(i.ioR1());
		uint32_t wrr2 = this->getReg(i.ioR2());
		uint32_t wraddr = i.shortAddr();

		if (wraddr == 0) {
			if (use_cache) {
				writeCache(wrr2, wrr1);
			}
			else {
			//	this->dma->write(wrr2 + (this->base * 4), wrr1);
			}
		}
		else {
			if (use_cache) {
				writeCache(wraddr, wrr1);
			}
			else {
				//this->dma->write(wraddr + (this->base * 4), wrr1);
			}
		}
	} break;

	case Opcode::LW: {
		int32_t addr = this->getReg(i.cimmB());
		uint32_t d = i.cimmD();

		// LW and ST are never used with a non-zero shortAddr, and it's unspecified
		// what they would do with a non-zero shortAddr, so this is the best I've got
		if (use_cache) {
			if (readCache(addr) == -1) {
				return;
			}
			setReg(d, readCache(addr));
		}
		else {
		//	this->setReg(d, this->dma->read(addr + (this->base * 4)));
		}
	} break;

	case Opcode::ST: {
		int32_t data = this->getReg(i.cimmB());
		int32_t addr = this->getReg(i.cimmD());

		if (use_cache) {
			writeCache(addr, data);
		}
		else {
		//	this->dma->write(addr + (this->base * 4), data);
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
			//	this->dma->write((i + (b * 4)), readCache(i));
			}
		}

		std::cout << "This is process " << running->pc.job_number;

		int16_t j = 0;
		for (int i = 0; i < running->pc.frames.size(); ++i) {
			while (valid[j] == false) {
				j += 4;
			}
			dma->write(running->pc.frames[i], readCache(j), readCache(j + 4), readCache(j + 8), readCache(j + 12));
			j += 16;
		}

		this->running->total_memory_in_use = memory->in_use;
		reset_valid();

		writePCBCache();

		std::stringstream output; 
		output << "Job Number " << running->pc.job_number;
		output << std::endl << "Instruction Cache ";
		output << std::endl;
		int end = running->pc.job_instruction_count * 4;
		output << "      00       04       08       0c" << std::endl;
		for (int i = 0; i < end; i += 16) {
			output << setfill('0') << setw(3) << right << hex << i << " | ";
			//printf("%03x | ", i);
			for (int j = i; j < i + 4 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.itCache[j];
				//printf("%02x", this->memory[j]);
			}
			output << " ";
			//printf(" ");
			for (int j = i + 4; j < i + 8 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.itCache[j];
			}
			output << " ";
			for (int j = i + 8; j < i + 12 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.itCache[j];
			}
			output << " ";
			for (int j = i + 12; j < i + 16 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.itCache[j];
			}
			output << dec << endl;
		}

		output << std::endl << "Input Cache" << std::endl;
		end = running->b.input_buffer * 4;
		output << "      00       04       08       0c" << std::endl;
		for (int i = 0; i < end; i += 16) {
			output << setfill('0') << setw(3) << right << hex << i << " | ";
			//printf("%03x | ", i);
			for (int j = i; j < i + 4 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.ipCache[j];
				//printf("%02x", this->memory[j]);
			}
			output << " ";
			//printf(" ");
			for (int j = i + 4; j < i + 8 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.ipCache[j];
			}
			output << " ";
			for (int j = i + 8; j < i + 12 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.ipCache[j];
			}
			output << " ";
			for (int j = i + 12; j < i + 16 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.ipCache[j];
			}
			output << dec << endl;
		}

		output << std::endl << "Output Cache" << std::endl;
		end = running->b.output_buffer * 4;
		output << "      00       04       08       0c" << std::endl;
		for (int i = 0; i < end; i += 16) {
			output << setfill('0') << setw(3) << right << hex << i << " | ";
			//printf("%03x | ", i);
			for (int j = i; j < i + 4 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.oCache[j];
				//printf("%02x", this->memory[j]);
			}
			output << " ";
			//printf(" ");
			for (int j = i + 4; j < i + 8 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.oCache[j];
			}
			output << " ";
			for (int j = i + 8; j < i + 12 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.oCache[j];
			}
			output << " ";
			for (int j = i + 12; j < i + 16 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.oCache[j];
			}
			output << dec << endl;
		}

		output << std::endl << "Temp Cache" << std::endl;
		end = running->b.temp_buffer * 4;
		output << "      00       04       08       0c" << std::endl;
		for (int i = 0; i < end; i += 16) {
			output << setfill('0') << setw(3) << right << hex << i << " | ";
			//printf("%03x | ", i);
			for (int j = i; j < i + 4 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.tempCache[j];
				//printf("%02x", this->memory[j]);
			}
			output << " ";
			//printf(" ");
			for (int j = i + 4; j < i + 8 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.tempCache[j];
			}
			output << " ";
			for (int j = i + 8; j < i + 12 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.tempCache[j];
			}
			output << " ";
			for (int j = i + 12; j < i + 16 && j < end; j++) {
				output << setfill('0') << setw(2) << right << hex << (int)running->pc.tempCache[j];
			}
			output << dec << endl;
		}

		std::ofstream file;
		file.open("..\\..\\job_memory.txt", std::ofstream::app);
		file << "Job #";
		file << (int)running->pc.job_number << endl;
		file << output.str() << endl;
		//file << "Data" << endl;
		//file << data << endl;
		file.close();
		

		for (int i = 0; i < this->running->pc.pages.size(); ++i) {
			memory->deallocate(this->running->pc.frames.at(i));
		}

		this->running->pc.process_status = TERMINATE;
		this->running->ios = dma->get_io_number();
		++num_processes;
		running->end = std::chrono::high_resolution_clock::now();
		load->get_terminated()->push_back(running);
		cout << " Size of terminated is " << load->get_terminated()->size() << endl;

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
		this->pc = i.longAddr() + (this->base);
	} break;

	case Opcode::BEQ: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b == d) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	case Opcode::BNE: {
		int32_t b = this->getReg(i.cimmB());
		int32_t d = this->getReg(i.cimmD());

		if (b != d) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	case Opcode::BEZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b == 0) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	case Opcode::BNZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b != 0) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	case Opcode::BGZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b > 0) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	case Opcode::BLZ: {
		int32_t b = this->getReg(i.cimmB());

		if (b < 0) {
			this->pc = i.shortAddr() + (this->base);
		}
	} break;

	default:
		disassembleInstruction(i);
	}
}

uint32_t CPU::readCache(uint16_t addr) {
	assert(addr % 4 == 0);
	if (valid[addr] == false) {
		while (addr % 16 != 0) {
			--addr;
		}
		running->pc.valid.at(addr/ 16) = false;
		writePCBCache();
		done = true;
		load->move_waiting(running);
		return -1;
	}
	int32_t result = cache[addr] << 24;
	result |= cache[addr + 1] << 16;
	result |= cache[addr + 2] << 8;
	result |= cache[addr + 3];
	return result;
}

void CPU::writeCache(uint16_t addr, int32_t data) {
	assert(addr % 4 == 0);
	if (valid[addr] == false) {
		while (addr % 16 != 0) {
			--addr;
		}
		running->pc.valid.at(addr / 16) = false;
		writePCBCache();
		done = true;
		load->move_waiting(running);
		return;
	}
	cache[addr] = data >> 24;
	cache[addr + 1] = data >> 16;
	cache[addr + 2] = data >> 8;
	cache[addr + 3] = data;
}

void CPU::writeOneCache(uint16_t addr, uint8_t data) {
	cache[addr] = data;
}

void CPU::writePCBCache() {
	uint16_t i;
	uint16_t j = 0;
	uint16_t p;
	cout << endl << "Instruction count " << running->pc.job_instruction_count << endl;
	for (i = 0; i < running->pc.job_instruction_count * 4; i += 4) {
		if (valid[i] == true) {
			running->pc.itCache[i] = cache[i];
			running->pc.itCache[i + 1] = cache[i + 1];
			running->pc.itCache[i + 2] = cache[i + 2];
			running->pc.itCache[i + 3] = cache[i + 3];
		}
	}
	cout << endl << " Finished this " << endl;
	p = i;
	for (i = i; i < (running->b.input_buffer * 4) + p; i += 4) {
		if (valid[i] == true) {
			running->pc.ipCache[j] = cache[i];
			running->pc.ipCache[j + 1] = cache[i + 1];
			running->pc.ipCache[j + 2] = cache[i + 2];
			running->pc.ipCache[j + 3] = cache[i + 3];
		}
		j += 4;
	}
	p = i;
	j = 0;
	for (i = i; i < (running->b.output_buffer* 4) + p; i += 4) {
		if (valid[i] == true || i == p) {
			running->pc.oCache[j] = cache[i];
			running->pc.oCache[j + 1] = cache[i + 1];
			running->pc.oCache[j + 2] = cache[i + 2];
			running->pc.oCache[j + 3] = cache[i + 3];
		}
		j += 4;
	}
	p = i;
	j = 0;
	cout << endl << "P is " << p << endl;
	cout << endl << "The temp buff is " << running->b.temp_buffer << endl;
	for (i = i; i < (running->b.temp_buffer * 4) + p; i += 4) {
		if (valid[i] == true) {
			running->pc.tempCache[j] = cache[i];
			running->pc.tempCache[j + 1] = cache[i + 1];
			running->pc.tempCache[j + 2] = cache[i + 2];
			running->pc.tempCache[j + 3] = cache[i + 3];
		}
		j += 4;
	}
	uint8_t l;
	for (l = 0; l < 16; ++l) {
		running->pc.registers[l] = getReg(l);
		std::cout << (int)registers[l];
	}
	running->pc.program_counter = this->pc;
}
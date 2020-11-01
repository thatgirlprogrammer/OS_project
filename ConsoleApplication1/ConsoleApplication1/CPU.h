#pragma once

#include "instruction.h"
#include "Memory.h"
#include "DMA.h"
#include "loader.h"

class CPU
{
public:
	CPU(Memory*, DMA*, int);

	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);

	void step();

	uint32_t getPC() { return this->pc; }
	void setPC() { pc = 0 + (this->base * 4); }
	void setBase(int b) { base = b; }
	bool isDone() { return this->done; }
	void setDone() { this->done = false; }
	bool isCache() { return use_cache; }
	void useCache() { use_cache = true; }
	uint32_t readCache(uint16_t addr);
	void writeCache(uint16_t addr, int32_t data);
	int cpu_num;
	void set_running(PCB_info* running) { this->running = running; }
	PCB_info* get_running() { return this->running; }
	DMA* dma;
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	uint32_t base;
	bool done = false;
	Memory* memory;
	bool use_cache = true;
	uint8_t cache[72 * 4];
	PCB_info* running = nullptr;
};
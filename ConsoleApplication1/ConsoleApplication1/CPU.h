#pragma once

#include "instruction.h"
#include "Memory.h"
#include "DMA.h"
#include "loader.h"
#include <string>

class CPU
{
public:
	CPU(Memory*, DMA*, int, loader*);
	int32_t getReg(uint8_t reg);
	void setReg(uint8_t reg, int32_t value);
	void step();

	uint32_t getPC() { return this->pc; }
	void setPC() { pc = 0; }
	void setValuePC(int value) { pc = value; }
	void writeRegisters(uint8_t index, int32_t value) { registers[index] = value; }
	void setBase(int b) { base = b; }
	bool isDone() { return this->done; }
	void setDone() { this->done = false; }
	bool isCache() { return use_cache; }
	void useCache() { use_cache = true; }
	uint32_t readCache(uint16_t addr);
	void writeCache(uint16_t addr, int32_t data);
	void writePCBCache();
	void writeOneCache(uint16_t addr, uint8_t data);
	int cpu_num;
	void set_running(PCB_info* running) { this->running = running; }
	PCB_info* get_running() { return this->running; }
	DMA* dma;
	int get_num_processes() { return num_processes; }
	void set_valid(int index, bool flag) { valid[index] = flag; }
	void reset_valid() {
		for (int i = 0; i < 400; ++i) {
			valid[i] = false;
		}
	}
	bool flag = false;
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	uint32_t base;
	bool done = false;
	Memory* memory;
	bool use_cache = true;
	uint8_t cache[100 * 4];
	bool valid[100 * 4] = { false };
	int num_processes = 0;
	PCB_info* running = nullptr;
	loader* load;
	
};

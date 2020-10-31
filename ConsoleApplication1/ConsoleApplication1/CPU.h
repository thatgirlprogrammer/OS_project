#pragma once

#include "instruction.h"
#include "Memory.h"
#include "DMA.h"
#include "loader.h"

class CPU
{
public:
	CPU(Memory*, DMA*, loader*);

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
	void appendRunning(PCB_info* pcb);
	void setTerminated(vector<PCB_info*>* term) { terminated = term; }
private:
	int32_t registers[REGISTER_COUNT];
	uint32_t pc;
	uint32_t base;
	bool done = false;
	Memory* memory;
	DMA* dma;
	bool use_cache = false;
	uint8_t cache[72 * 4];
	vector<PCB_info*>* private_running = new vector<PCB_info*>;
	vector<PCB_info*>* terminated;
	loader* load;
};

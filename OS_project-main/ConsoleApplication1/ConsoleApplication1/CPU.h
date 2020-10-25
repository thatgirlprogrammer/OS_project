#pragma once

#include "instruction.h"
#include "long_term_scheduler.h"
#include "PCB.h"

namespace OSSim 
{
	constexpr uint8_t REGISTER_COUNT = 16;
	constexpr uint32_t MEMORY = 1024;

	class CPU
	{
	public:
		CPU();
		void load_into_ram(vector<uint32_t>* val, PCB_info pcb);
		int32_t getReg(uint8_t reg);
		void setReg(uint8_t reg, int32_t value);
		void step();
	private:
		int32_t registers[REGISTER_COUNT];
		uint32_t pc;
		int32_t memory[MEMORY];
		ram* ram1;
	};
}

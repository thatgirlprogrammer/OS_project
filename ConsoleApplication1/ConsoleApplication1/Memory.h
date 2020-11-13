#pragma once

#include <string>
#include <sstream>
#include <cstdint>
#include "frame.h"
#include <mutex>

constexpr uint8_t REGISTER_COUNT = 16;
constexpr uint32_t MEMORY = 1024 * 4;

class Memory
{
public:
	Memory() {
		for (uint32_t i = 0; i < MEMORY; i++)
			this->memory[i] = 0;
		for (int i = 0; i < 256; ++i) {
			fr[i] = new frame();
		}
	}

	int32_t getMem(int num, int offset);
	void setMem(int num, int32_t data1, int32_t data2, int32_t data3, int32_t data4);
	bool hasHole(int pages);
	bool isOccupied(int num);
	void deallocate(int num);
	int freeFrame();
	//std::string dump();
	unsigned long in_use = 0;
private:
	uint8_t memory[MEMORY];
	frame* fr[256];
	std::mutex mtx;
};

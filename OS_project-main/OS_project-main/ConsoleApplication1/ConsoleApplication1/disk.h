#pragma once
#include <cstddef>
#include <cstdint>
#include "page.h"
/*
 * Class disk simulates a physical disk
 * running on a machine. Its job is to allocate
 * and deallocate storage in permanent storage.
 * It handles reads and writes to disk.
 * */
using namespace std;
class disk{
private:
	/*
	 * int size represents the amount of words
	 * available for storage on system.
	 * int free space is the amount of space available
	 * on machine.
	 * uint_8 storage is the storage available to the
	 * machine.
	 * */
	const int size = 2048;
	int free_space;
	page* pages[512];
	int page_size = 4;
	int free_blocks = 512;
	int used_blocks = 0;
public:
	/*
	 * Method declaration.
	 * */
	disk();
	
	int32_t read(int pg, int offset);
	void write(int pg, int32_t value1, int32_t value2, int32_t value3, int32_t value4);

};
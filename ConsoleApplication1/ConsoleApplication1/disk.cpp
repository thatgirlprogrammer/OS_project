#include "disk.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <cassert>

/*
 * disk implementation file.
 * */
using namespace std;

/*
 * Constructor for disk class.
 * Initializes free_space and storage.
 * */
disk::disk() {
	free_space = size;
	for (int i = 0; i < 512; ++i) {
		pages[i] = new page();
	}
}


/*
 * read returns the item in the memory block
 * index.
 * */
int32_t disk::read(int pg, int offset) {
	return pages[pg]->getData(offset);
}
/*
 * write adds a specified value to a memory block
 * and decrements free_space if that space was
 * already empty.
 * */
void disk::write(int pg, int32_t value1, int32_t value2, int32_t value3, int32_t value4) {
	pages[pg]->writeData(value1, value2, value3, value4);
}
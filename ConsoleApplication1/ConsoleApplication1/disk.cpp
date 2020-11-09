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
	fill_n(storage, size, 0);
}

/*
 * deallocate removes a block from memory
 * if not already empty.
 * */
void disk::deallocate(int index) {
	if (storage[index] != 0) {
		free_space++;
	}
	storage[index] = 0;
}
/*
 * reformat removes all items from memory
 * and creates new storage.
 * */
void disk::reformat() {
	fill_n(storage, size, 0);
}
/*
 * read returns the item in the memory block
 * index.
 * */
int32_t disk::read(int index) {
	return storage[index];
}
/*
 * write adds a specified value to a memory block
 * and decrements free_space if that space was
 * already empty.
 * */
void disk::write(int32_t value1, int32_t value2, int32_t value3, int32_t value4, int index) {
	assert(index % 4 == 0);
	if (storage[index] == 0) {
		free_space-= 4;
		--free_blocks;
	}
	storage[index] = value1;
	storage[index + 1] = value2;
	storage[index + 2] = value3;
	storage[index + 3] = value4;
}
/*
 * get_space returns the value of
 * free_space
 * */
int disk::get_space() {
	return free_space;
}
/*
 * get_chunk returns a larger chunk of specified
 * memory as needed.
 * */
int32_t* disk::get_chunk(int index, int length) {
	int32_t* temp = new int32_t[length];
	for (int i = 0; i < length; ++i) {
		temp[i] = storage[index + i];
	}
	return temp;
}
/*
 * delete_chunk deletes a larger chunk of specified
 * memory as needed.
 * */
void disk::delete_chunk(int index, int length) {
	for (int i = index; i < index + length; ++i) {
		if (storage[i] != 0) {
			free_space++;
		}
		storage[i] = 0;
	}
}

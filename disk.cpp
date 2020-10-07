#include "disk.h"
#include <string>

/*
 * disk implementation file.
 * */
using namespace std;

/*
 * Constructor for disk class.
 * Initializes free_space and storage.
 * */
disk::disk(){
	free_space = size;
	storage = new string[size];
}

/*
 * deallocate removes a block from memory
 * if not already empty.
 * */
void disk::deallocate(int index){
	if (!storage[index].empty()){
		free_space++;
	}
	storage[index].erase();
}
/*
 * reformat removes all items from memory
 * and creates new storage.
 * */
void disk::reformat(){
	delete[] storage;
	storage = new string[size];
	free_space = size;
}
/*
 * read returns the item in the memory block
 * index.
 * */
string disk::read(int index){
	return storage[index];
}
/*
 * write adds a specified value to a memory block
 * and decrements free_space if that space was
 * already empty.
 * */
void disk::write(string value, int index){
	if (storage[index].empty()){
		free_space --;
	}
	storage[index] = value;
}
/*
 * get_space returns the value of
 * free_space
 * */
int disk::get_space(){
	return free_space;
}
/*
 * get_chunk returns a larger chunk of specified
 * memory as needed.
 * */
string* disk::get_chunk(int index, int length){
	string* temp = new string[length];
	for (int i = 0; i < length; ++i){
		temp[i] = storage[index + i];
	}
	return temp;
}
/*
 * delete_chunk deletes a larger chunk of specified
 * memory as needed.
 * */
void disk::delete_chunk(int index, int length){
	for (int i = index; i < index + length; ++i){
		if (!storage[i].empty()){
			free_space++;
		}
		storage[i].erase();
	}
}
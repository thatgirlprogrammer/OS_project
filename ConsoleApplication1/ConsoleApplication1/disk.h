#include <cstddef>
#include <cstdint>
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
	uint8_t storage[2048];
public:
	/*
	 * Method declaration.
	 * */
	disk();
	void deallocate(int index);
	void reformat();
	uint8_t read(int index);
	void write(uint8_t value, int index);
	int get_space();
	uint8_t* get_chunk(int index, int length);
	void delete_chunk(int index, int length);
};

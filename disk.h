#include <string>
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
	 * string* storage is the storage available to the
	 * machine.
	 * */
	const int size = 2048;
	int free_space;
	string* storage = NULL;
public:
	/*
	 * Method declaration.
	 * */
	disk();
	void deallocate(int index);
	void reformat();
	string read(int index);
	void write(string value, int index);
	int get_space();
	string* get_chunk(int index, int length);
	void delete_chunk(int index, int length);
};
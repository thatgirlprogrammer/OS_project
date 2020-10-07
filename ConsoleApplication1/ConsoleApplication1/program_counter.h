#pragma once
#include <string>

class program_counter
{
public:
	program_counter();
	~program_counter();
	void update_counter();
	int get_counter();
private:
	int counter;
};

#pragma once
#include <string>
#include <vector>

class instruction_register
{
public:
	instruction_register(std::vector<std::string>* instructions);
	~instruction_register();
	std::string get_instruction(int index);
private:
	std::vector<std::string>* instructions;
};


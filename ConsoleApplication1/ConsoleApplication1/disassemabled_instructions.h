#pragma once
#include "instruction.h"
class disassemabled_instructions
{
public:
	disassemabled_instructions(Opcode op, int val1, int val2, int val3) 
	{
		opcode = op;
		this->val1 = val1;
		this->val2 = val2;
		this->val3 = val3;
	}

	Opcode get_opcode() {
		return opcode;
	}

	int get_val1() {
		return val1;
	}

	int get_val2() {
		return val2;
	}

	int get_val3() {
		return val3;
	}
private:
	Opcode opcode;
	int val1;
	int val2;
	int val3;

};


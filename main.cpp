#include <stdio.h>
#include <iostream>

#include "Instruction.h"
#include "Disassemble.h"

using namespace std;

int main() {
	Instruction i = Instruction(0x4bd63000);
	cout << (i.opcode() == Opcode::MOVI) << endl;

	std::vector<Instruction> v;

	v.push_back(Instruction(0xC050005C));
	v.push_back(Instruction(0x4B060000));
	v.push_back(Instruction(0x4B010000));
	v.push_back(Instruction(0x4B000000));
	v.push_back(Instruction(0x4F0A005C));
	v.push_back(Instruction(0x4F0D00DC));
	v.push_back(Instruction(0x4C0A0004));
	v.push_back(Instruction(0xC0BA0000));
	v.push_back(Instruction(0x42BD0000));
	v.push_back(Instruction(0x4C0D0004));
	v.push_back(Instruction(0x4C060001));
	v.push_back(Instruction(0x10658000));
	v.push_back(Instruction(0x56810018));
	v.push_back(Instruction(0x4B060000));
	v.push_back(Instruction(0x4F0900DC));
	v.push_back(Instruction(0x43970000));
	v.push_back(Instruction(0x05070000));
	v.push_back(Instruction(0x4C060001));
	v.push_back(Instruction(0x4C090004));
	v.push_back(Instruction(0x10658000));
	v.push_back(Instruction(0x5681003C));
	v.push_back(Instruction(0xC10000AC));
	v.push_back(Instruction(0x92000000));

	disassemble(v);
}
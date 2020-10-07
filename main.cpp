#include <stdio.h>
#include <iostream>

#include "Instruction.h"

using namespace std;

int main() {
	cout << "Hello" << endl;

	Instruction i = Instruction(0x4bd63000);
	cout << (i.opcode() == Opcode::MOVI) << endl;
}
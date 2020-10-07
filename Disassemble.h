#pragma once

#include <vector>

#include "Instruction.h"

const char* opcodeToString(Opcode);
void disassemble(std::vector<Instruction>);


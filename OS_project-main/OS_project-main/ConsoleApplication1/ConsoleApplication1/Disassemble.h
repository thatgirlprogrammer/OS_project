#pragma once

#include <vector>

#include "Instruction.h"

const char* opcodeToString(Opcode);
void disassembleInstruction(Instruction);
void disassemble(std::vector<Instruction>);


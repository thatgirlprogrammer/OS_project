#pragma once

#include <vector>
#include "disassemabled_instructions.h"
#include "Instruction.h"

const char* opcodeToString(Opcode);
disassemabled_instructions* disassembleInstruction(Instruction);
std::vector<disassemabled_instructions> disassemble(std::vector<Instruction>);

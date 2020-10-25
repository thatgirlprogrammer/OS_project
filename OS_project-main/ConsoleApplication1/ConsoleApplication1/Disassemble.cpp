#include <iostream>
#include "disassemabled_instructions.h"
#include "Disassemble.h"

const char* opcodeToString(Opcode op) {
	switch (op) {
	case Opcode::RD:   return "c0 RD  ";
	case Opcode::WR:   return "c1 WR  ";
	case Opcode::ST:   return "42 ST  ";
	case Opcode::LW:   return "43 LW  ";
	case Opcode::MOV:  return "04 MOV ";
	case Opcode::ADD:  return "05 ADD ";
	case Opcode::SUB:  return "06 SUB ";
	case Opcode::MUL:  return "07 MUL ";
	case Opcode::DIV:  return "08 DIV ";
	case Opcode::AND:  return "09 AND ";
	case Opcode::OR:   return "0a OR  ";
	case Opcode::MOVI: return "4b MOVI";
	case Opcode::ADDI: return "4c ADDI";
	case Opcode::MULI: return "4d MULI";
	case Opcode::DIVI: return "4e DIVI";
	case Opcode::LDI:  return "4f LDI ";
	case Opcode::SLT:  return "10 SLT ";
	case Opcode::SLTI: return "51 SLTI";
	case Opcode::HLT:  return "92 HLT ";
	case Opcode::NOP:  return "13 NOP ";
	case Opcode::JMP:  return "00 JMP ";
	case Opcode::BEQ:  return "54 BEQ ";
	case Opcode::BNE:  return "56 BNE ";
	case Opcode::BEZ:  return "57 BEZ ";
	case Opcode::BNZ:  return "58 BNZ ";
	case Opcode::BGZ:  return "59 BGZ ";
	case Opcode::BLZ:  return "5a BLZ ";
	}

	assert(false);
	return "";
}

disassemabled_instructions* disassembleInstruction(Instruction ins) {
	std::cout << opcodeToString(ins.opcode());
	switch (ins.opcodeType()) {
	case OpcodeType::ARITHMETIC:
		std::cout << "\ts1: " << (int)ins.arithS1() << "\ts2: " << (int)ins.arithS2() << "\td: " << (int)ins.arithD() << std::endl;
		return new disassemabled_instructions(ins.opcode(), (int)ins.arithS1(), (int)ins.arithS2(), (int)ins.arithD());
	case OpcodeType::CONDIMM:
		std::cout << "\tb: " << (int)ins.cimmB() << "\td: " << (int)ins.cimmD() << "\taddr: " << std::hex << (int)ins.shortAddr() << std::dec << std::endl;
		return new disassemabled_instructions(ins.opcode(), (int)ins.cimmB(), (int)ins.cimmB(), (int)ins.shortAddr());
	case OpcodeType::JUMP:
		std::cout << "\taddr: " << (int)ins.longAddr() << std::endl;
		return new disassemabled_instructions(ins.opcode(), (int)ins.longAddr(), 0, 0);
	case OpcodeType::IO:
		std::cout << "\tr1: " << (int)ins.ioR1() << "\tr2: " << (int)ins.ioR2() << "\taddr: " << std::hex << (int)ins.shortAddr() << std::dec << std::endl;
		return new disassemabled_instructions(ins.opcode(), (int)ins.ioR1(), (int)ins.ioR2(), (int)ins.shortAddr());
	}
	return new disassemabled_instructions(Opcode::HLT, 0, 0, 0);
}

std::vector<disassemabled_instructions> disassemble(std::vector<Instruction> ins) {
	std::vector<disassemabled_instructions> instructions;
	for (std::vector<Instruction>::iterator it = ins.begin(); it != ins.end(); it++) {
		instructions.push_back(*disassembleInstruction(*it));
	}
	return instructions;
}

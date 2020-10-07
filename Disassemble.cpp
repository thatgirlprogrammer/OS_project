#include <iostream>

#include "Disassemble.h"

const char* opcodeToString(Opcode op) {
	switch (op) {
	case Opcode::RD:   return "RD  ";
	case Opcode::WR:   return "WR  ";
	case Opcode::ST:   return "ST  ";
	case Opcode::LW:   return "LW  ";
	case Opcode::MOV:  return "MOV ";
	case Opcode::ADD:  return "ADD ";
	case Opcode::SUB:  return "SUB ";
	case Opcode::MUL:  return "MUL ";
	case Opcode::DIV:  return "DIV ";
	case Opcode::AND:  return "AND ";
	case Opcode::OR:   return "OR  ";
	case Opcode::MOVI: return "MOVI";
	case Opcode::ADDI: return "ADDI";
	case Opcode::MULI: return "MULI";
	case Opcode::DIVI: return "DIVI";
	case Opcode::LDI:  return "LDI ";
	case Opcode::SLT:  return "SLT ";
	case Opcode::SLTI: return "SLTI";
	case Opcode::HLT:  return "HLT ";
	case Opcode::NOP:  return "NOP ";
	case Opcode::JMP:  return "JMP ";
	case Opcode::BEQ:  return "BEQ ";
	case Opcode::BNE:  return "BNE ";
	case Opcode::BEZ:  return "BEZ ";
	case Opcode::BNZ:  return "BNZ ";
	case Opcode::BGZ:  return "BGZ ";
	case Opcode::BLZ:  return "BLZ ";
	}

	assert(false);
	return "";
}

void disassemble(std::vector<Instruction> ins) {
	for (std::vector<Instruction>::iterator it = ins.begin(); it != ins.end(); it++) {
		std::cout << opcodeToString(it->opcode());

		switch (it->opcodeType()) {
		case OpcodeType::ARITHMETIC:
			std::cout << "\ts1: " << (int)it->arithS1() << "\ts2: " << (int)it->arithS2() << "\td: " << (int)it->arithD();
			break;
		case OpcodeType::CONDIMM:
			std::cout << "\tb: " << (int)it->cimmB() << "\td: " << (int)it->cimmD() << "\taddr: " << std::hex << (int)it->shortAddr() << std::dec;
			break;
		case OpcodeType::JUMP:
			std::cout << "\taddr: " << (int)it->longAddr();
			break;
		case OpcodeType::IO:
			std::cout << "\tr1: " << (int)it->ioR1() << "\tr2: " << (int)it->ioR2() << "\taddr: " << std::hex << (int)it->shortAddr() << std::dec;
			break;
		}

		std::cout << std::endl;
	}
}

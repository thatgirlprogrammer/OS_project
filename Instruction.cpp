#include <cstdint>
#include <assert.h>

#include "Instruction.h"

Instruction::Instruction(uint32_t inst) {
	this->inst = inst;
	this->type = (OpcodeType)(inst >> 30);

	bool ok = false;
	Opcode op = this->opcode();

	switch (this->type) {
	case OpcodeType::ARITHMETIC:
		ok = op == Opcode::MOV
			|| op == Opcode::ADD
			|| op == Opcode::SUB
			|| op == Opcode::MUL
			|| op == Opcode::DIV
			|| op == Opcode::AND
			|| op == Opcode::OR
			|| op == Opcode::SLT;
		break;
	case OpcodeType::CONDIMM:
		ok = op == Opcode::ST
			|| op == Opcode::LW
			|| op == Opcode::MOVI
			|| op == Opcode::ADDI
			|| op == Opcode::MULI
			|| op == Opcode::DIVI
			|| op == Opcode::LDI
			|| op == Opcode::SLTI
			|| op == Opcode::BEQ
			|| op == Opcode::BNE
			|| op == Opcode::BEZ
			|| op == Opcode::BNZ
			|| op == Opcode::BGZ
			|| op == Opcode::BLZ;
		break;
	case OpcodeType::JUMP:
		ok = op == Opcode::HLT || op == Opcode::JMP;
		break;
	case OpcodeType::IO:
		ok = op == Opcode::RD || op == Opcode::WR;
		break;
	}

	assert(ok);
}

Opcode Instruction::opcode() {
	return (Opcode)((this->inst >> 24) & 0x3f);
}

uint8_t Instruction::arithS1() {
	assert(this->type == OpcodeType::ARITHMETIC);
	return arg1();
}

uint8_t Instruction::arithS2() {
	assert(this->type == OpcodeType::ARITHMETIC);
	return arg2();
}

uint8_t Instruction::arithD() {
	assert(this->type == OpcodeType::ARITHMETIC);
	return arg3();
}

uint8_t Instruction::cimmB() {
	assert(this->type == OpcodeType::CONDIMM);
	return arg1();
}

uint8_t Instruction::cimmD() {
	assert(this->type == OpcodeType::CONDIMM);
	return arg2();
}

uint8_t Instruction::ioR1() {
	assert(this->type == OpcodeType::IO);
	return arg1();
}

uint8_t Instruction::ioR2() {
	assert(this->type == OpcodeType::IO);
	return arg2();
}

uint16_t Instruction::shortAddr() {
	assert(this->type == OpcodeType::CONDIMM || this->type == OpcodeType::IO);
	return this->inst & 0xffff;
}

uint32_t Instruction::longAddr() {
	assert(this->type == OpcodeType::JUMP);
	return this->inst & 0xffff;
}

uint8_t Instruction::arg1() {
	return (this->inst >> 20) & 0x0f;
}

uint8_t Instruction::arg2() {
	return (this->inst >> 16) & 0x0f;
}

uint8_t Instruction::arg3() {
	return (this->inst >> 12) & 0x0f;
}

#pragma once
#include <cstdint>
#include <cassert>
#include <vector>


enum class Opcode {
	RD,
	WR,
	ST,
	LW,
	MOV,
	ADD,
	SUB,
	MUL,
	DIV,
	AND,
	OR,
	MOVI,
	ADDI,
	MULI,
	DIVI,
	LDI,
	SLT,
	SLTI,
	HLT,
	NOP,
	JMP,
	BEQ,
	BNE,
	BEZ,
	BNZ,
	BGZ,
	BLZ,
};

enum class OpcodeType {
	ARITHMETIC,
	CONDIMM,
	JUMP,
	IO,
};

class Instruction {
public:
	explicit Instruction(uint32_t inst);
	Opcode opcode();
	OpcodeType opcodeType() { return this->type; }

	// Arithmetic instruction arguments
	uint8_t arithS1();
	uint8_t arithS2();
	uint8_t arithD();

	// Conditional/immediate instruction arguments
	uint8_t cimmB();
	uint8_t cimmD();

	// IO instruction arguments
	uint8_t ioR1();
	uint8_t ioR2();

	// Addresses
	uint16_t shortAddr();
	uint32_t longAddr();
	uint32_t get_inst() {
		return inst;
	}

private:
	uint32_t inst;
	OpcodeType type;

	// Instruction arguments
	uint8_t arg1();
	uint8_t arg2();
	uint8_t arg3();
};

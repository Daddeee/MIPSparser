#ifndef MIPS_DEFINITIONS_H
#define MIPS_DEFINITIONS_H
// Manage instruction and register's list.
//-------------------------------------------------------

#include "macro.h"

#define _INSTRUCTION_TYPE_LIST(code) \
	code(R)		\
	code(I)		\
	code(J)		\

// why _div and not just div?

#define _R_ISTR_LIST(code)	\
	code(add)	\
	code(sub)	\
	code(mul)	\
	code(div)	\
	code(and)	\
	code(or)	\
	code(xor)	\
	code(nor)	\
	code(slt)	\
	code(sll)	\
	code(srl)	\
	code(sra)	\

#define _I_ISTR_LIST(code)	\
	code(addi)	\
	code(andi)	\
	code(ori)	\
	code(xori)	\
	code(beq)	\
	code(bneq)	\
	code(lw)	\
	code(sw)	\
	code(lb)	\
	code(sb)	\
	code(lh)	\
	code(sh)	\

#define _J_ISTR_LIST(code)	\
	code(j) 	\
	code(jal)	\

#define _REGISTER_LIST(code) \
	code($zero)	\
	code($at)	\
	code($v0)	\
	code($v1)	\
	code($a0)	\
	code($a1)	\
	code($a2)	\
	code($a3)	\
	code($t0)	\
	code($t1)	\
	code($t2)	\
	code($t3)	\
	code($t4)	\
	code($t5)	\
	code($t6)	\
	code($t7)	\
	code($s0)	\
	code($s1)	\
	code($s2)	\
	code($s3)	\
	code($s4)	\
	code($s5)	\
	code($s6)	\
	code($s7)	\
	code($t8)	\
	code($t9)	\
	code($k0)	\
	code($k1)	\
	code($gp)	\
	code($sp)	\
	code($fp)	\
	code($ra)	\

DECLARE_ENUM(instruction_type, _INSTRUCTION_TYPE_LIST)

DECLARE_ENUM(registers, _REGISTER_LIST)
DECLARE_ENUM(r_instructions, _R_ISTR_LIST)
DECLARE_ENUM(i_instructions, _I_ISTR_LIST)
DECLARE_ENUM(j_instructions, _J_ISTR_LIST)

DECLARE_STRING_TO_ENUM(registers)
DECLARE_STRING_TO_ENUM(r_instructions)
DECLARE_STRING_TO_ENUM(i_instructions)
DECLARE_STRING_TO_ENUM(j_instructions)

//-------------------------------------------------------
// Basic definitions
//-------------------------------------------------------

struct r_istr {
	enum r_instructions instr;
	enum registers rd;
	enum registers rs;
	enum registers rt;
};

struct i_istr {
	enum i_instructions instr;
	enum registers rd;
	enum registers rs;
	int imm;
};

struct j_istr {
	enum j_instructions instr;
	enum registers rd;
};

typedef struct instr_t {
	enum instruction_type type;
	union {
		struct r_istr r;
		struct i_istr i;
		struct j_istr j;
	} params;
} instruction;

instruction build_instruction(enum instruction_type, ...);

#endif
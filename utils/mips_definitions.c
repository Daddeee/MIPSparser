#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define div __not_div__
#include <stdlib.h>
#undef div

#include "mips_definitions.h"

DEFINE_STRING_TO_ENUM(i_instructions, _I_ISTR_LIST)
DEFINE_STRING_TO_ENUM(r_instructions, _R_ISTR_LIST)
DEFINE_STRING_TO_ENUM(j_instructions, _J_ISTR_LIST)
DEFINE_STRING_TO_ENUM(registers, _REGISTER_LIST)

DEFINE_ENUM_TO_STRING(i_instructions, _I_ISTR_LIST)
DEFINE_ENUM_TO_STRING(r_instructions, _R_ISTR_LIST)
DEFINE_ENUM_TO_STRING(j_instructions, _J_ISTR_LIST)
DEFINE_ENUM_TO_STRING(registers, _REGISTER_LIST)

instruction build_instruction(enum instruction_type t, ...){
	va_list ap;
	instruction x;

	x.type = t; 
	va_start(ap, t);

	switch(t){
		case R:
			x.params.r.instr 	= va_arg(ap, enum r_instructions);
			x.params.r.rd		= va_arg(ap, enum registers);
			x.params.r.rs		= va_arg(ap, enum registers);
			x.params.r.rt		= va_arg(ap, enum registers);
			break;
		case I:
			x.params.i.instr 	= va_arg(ap, enum i_instructions);
			x.params.i.rd		= va_arg(ap, enum registers);
			x.params.i.rs		= va_arg(ap, enum registers);
			x.params.i.imm		= va_arg(ap, int);
			break;
		case J:
			x.params.j.instr 	= va_arg(ap, enum j_instructions);
			x.params.j.rd		= va_arg(ap, enum registers);
			break;
	}

	va_end(ap);

	return x;
}

void instruction_dump(instruction x, FILE * f){
	char * instr;
	char * rd;
	char * rs;
	char * rt;
	int imm;

	switch(x.type){
		case R:
			instr = r_instructions_enum_to_string(x.params.r.instr);
			rd = registers_enum_to_string(x.params.r.rd);
			rs = registers_enum_to_string(x.params.r.rs);
			rt = registers_enum_to_string(x.params.r.rt);
			printf("%s\t%s\t%s\t%s\n", instr, rd, rs, rt);
			break;
		case I:
			instr = i_instructions_enum_to_string(x.params.i.instr);
			rd = registers_enum_to_string(x.params.i.rd);
			rs = registers_enum_to_string(x.params.i.rs);
			imm = x.params.i.imm;
			printf("%s\t%s\t%s\t%d\n", instr, rd, rs, imm);
			break;
		case J:
			instr = j_instructions_enum_to_string(x.params.j.instr);
			rd = registers_enum_to_string(x.params.j.rd);
			printf("%s\t%s\n", instr, rd);
			break;
	}
}
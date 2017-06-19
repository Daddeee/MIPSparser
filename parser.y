%{

#include <stdio.h>

#define div __not_div__
#include <stdlib.h>
#undef div

#include "utils/mips_definitions.h"
#include "utils/vector.h"

extern int yylex();
extern int yyparse();
extern int yylineno;
extern FILE* yyin;

void yyerror(const char* s);

Vector v;

%}

%union {
	int ival;
	char * tval;
}

%token <tval> REGISTER
%token <tval> IOPCODE
%token <tval> ROPCODE
%token <tval> JOPCODE
%token <tval> IMOPCODE
%token <ival> IMMEDIATE
%token <ival> EOL
%token <tval> OBRACKET
%token <tval> CBRACKET

%start instructions_sequence

%%

instructions_sequence: /* nothing */
	|	instruction instructions_sequence
	;

instruction: 
		ROPCODE REGISTER REGISTER REGISTER EOL
		{
			enum instruction_type t = R;
			enum r_instructions ropcode = r_instructions_string_to_enum($1);
			enum registers rd = registers_string_to_enum($2);
			enum registers rs = registers_string_to_enum($3);
			enum registers rt = registers_string_to_enum($4);
			instruction tmp = build_instruction(t, ropcode, rd, rs, rt);
			vector_append(&v, tmp);
		}
	|	IOPCODE REGISTER REGISTER IMMEDIATE EOL
		{
			enum instruction_type t = I;
			enum i_instructions iopcode = i_instructions_string_to_enum($1);
			enum registers rd = registers_string_to_enum($2);
			enum registers rs = registers_string_to_enum($3);
			int imm = $4;
			instruction tmp = build_instruction(t, iopcode, rd, rs, imm);
			vector_append(&v, tmp);
		}
	|	IMOPCODE REGISTER IMMEDIATE OBRACKET REGISTER CBRACKET EOL
		{
			enum instruction_type t = I;
			enum i_instructions iopcode = i_instructions_string_to_enum($1);
			enum registers rd = registers_string_to_enum($2);
			int imm = $3;
			enum registers rs = registers_string_to_enum($5);
			instruction tmp = build_instruction(t, iopcode, rd, rs, imm);
			vector_append(&v, tmp);
		}
	|	JOPCODE REGISTER EOL
		{
			enum instruction_type t = J;
			enum j_instructions jopcode = j_instructions_string_to_enum($1);
			enum registers rd = registers_string_to_enum($2);
			instruction tmp = build_instruction(t, jopcode, rd);
			vector_append(&v, tmp);
		}
	;
%%

int main() {
	int i;
	vector_init(&v);

	yyin = stdin;
	yyparse();

	for(i = 0; i < v.size; i++)
		instruction_dump(v.data[i], stdin);
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}

%option noyywrap yylineno

%{
#include <stdio.h>

#define YY_DECL int yylex()

#include "parser.tab.h"

%}

 /* 
Different opcode means different instruction's "syntax":

 	Register instructions: 				Opcode	RD	RS	RT
	Immediate mat/branch instructions:	Opcode	RD	RS	IMM
	Immediate memory instructions:		Opcode 	RD	IMM(RS)
	Jump Instructions:					Opcode 	RD
 
for each different syntax there's a new inclusive start state. 
 */
%s MATCHING_R
%s MATCHING_J
%s MATCHING_I

/* DEFINING REGEXP MACRO */

 /* Matching Registers */
REGISTER (\$(zero|at|gp|sp|fp|ra|[kv][0-1]|a[0-3]|t[0-9]|s[0-7]))
 
 /* Matching Immediates (signed integers) */
IMMEDIATE (?:0|[-|+]?[1-9][0-9]*)
 
 /* Register instructions */
R_INSTRUCTION ("add"|"sub"|"mul"|"div"|"and"|"or"|"xor"|"nor"|"slt"|"sll"|"srl"|"sra")
 
 /* Immediate instructions */
I_INSTRUCTION ("addi"|"subi"|"andi"|"ori"|"xori"|"beq"|"bneq")
I_MEM_INSTRUCTION ("lw"|"sw"|"lh"|"sh"|"lb"|"sb")
 
 /* Jump instructions */
J_INSTRUCTION ("j"|"jal")

%%

^{R_INSTRUCTION}		{ BEGIN(MATCHING_R); yylval.tval = strdup(yytext); return ROPCODE; }
^{J_INSTRUCTION}		{ BEGIN(MATCHING_J); yylval.tval = strdup(yytext); return JOPCODE; }
^{I_INSTRUCTION}		{ BEGIN(MATCHING_I); yylval.tval = strdup(yytext); return IOPCODE; }
^{I_MEM_INSTRUCTION}	{ BEGIN(MATCHING_I); yylval.tval = strdup(yytext); return IMOPCODE; }

<MATCHING_R>{REGISTER}	{ yylval.tval = strdup(yytext); return REGISTER; }
<MATCHING_I>{REGISTER}	{ yylval.tval = strdup(yytext); return REGISTER; }
<MATCHING_I>{IMMEDIATE}	{ yylval.ival = atoi(yytext); return IMMEDIATE; }
<MATCHING_J>{REGISTER}	{ yylval.tval = strdup(yytext); return REGISTER; }

\n 						{ BEGIN(INITIAL); return EOL; }
[ \t]+					{ /* Ignoring whitespaces and tabs */ }
\(						{ yylval.tval = strdup(yytext); return OBRACKET; }
\)						{ yylval.tval = strdup(yytext); return CBRACKET; }
.						{ /* manage errors bitch */ }

%%
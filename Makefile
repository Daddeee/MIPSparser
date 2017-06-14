all: parser
	rm parser.tab.c lex.yy.c parser.tab.h

parser.tab.c parser.tab.h:	parser.y
	bison -d parser.y

lex.yy.c: parser.l parser.tab.h
	flex parser.l

parser: lex.yy.c parser.tab.c parser.tab.h
	gcc -o parser parser.tab.c lex.yy.c utils/vector.c utils/mips_definitions.c -g

clean:
	rm parser parser.tab.c lex.yy.c parser.tab.h

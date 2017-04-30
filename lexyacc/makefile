y.tab.c y.tab.h: parser.y parser.h
	yacc -d parser.y

lex.yy.c: lexer.l
	lex lexer.l

# # If we want to test the parser (remember to uncomment main in marser.y)
# parser: parser.y parser.h lex.yy.c y.tab.h y.tab.c
# 	cc lex.yy.c y.tab.c y.tab.h -o parser

interpreter: interpreter.c parser.h y.tab.c lex.yy.c y.tab.h
	gcc -Wall -g interpreter.c paramlist.c funclist.c lex.yy.c y.tab.c -o interpreter -std=c99 -lm
	rm y.tab.c
	rm lex.yy.c
	rm y.tab.h

y.tab.c: calc.y
	yacc -d calc.y

y.tab.h: calc.y
	yacc -d calc.y

lex.yy.c: calc.l
	lex calc.l

calc: lex.yy.c y.tab.c y.tab.h
	cc lex.yy.c y.tab.c y.tab.h -o calc

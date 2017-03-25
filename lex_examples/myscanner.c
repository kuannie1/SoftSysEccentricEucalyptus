/*
Using the lex file to make tokenizer
Taken from this video: https://youtu.be/54bo1qaHAfk?t=12m42s
What a tokenizer is: https://en.wikipedia.org/wiki/Tokenization_(lexical_analysis)

How to run
$ lex myscanner.l   								 (run this command each time you change this file)
$ cc myscanner.c lex.yy.c -o myscanner               (cc was used in the video, gcc works too)
$ ./myscanner <config.in 
*/


#include <stdio.h>
#include "myscanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "db_type", "db_name", "db_table_prefix", "db_port"};

int main(void) 
{
	int ntoken, vtoken;

	ntoken = yylex();
	while(ntoken) {
		printf("%d\n", ntoken);
		if (yylex() != COLON) {
			printf("Syntax error is in line %d, Expected a ':' but found %s\n", yylineno, yytext);
			return 1;
		}
		vtoken = yylex();
		switch (ntoken) {
		case TYPE:
		case NAME:
		case TABLE_PREFIX:
			if (vtoken != IDENTIFIER) {
				printf("Syntax error is in line %d, Expected a ':' but found %s\n", yylineno, yytext);
				return 1;
			}
			printf("%s is set to %s\n", names[ntoken], yytext);
			break;
		case PORT:
			if (vtoken != INTEGER) {
				printf("Syntax error in line %d, Expected an integer but found %s\n", yylineno, yytext);
				return 1;
			}
			printf("%s is set to %s\n", names[ntoken], yytext);
			break;
		default:
			printf("Syntax error in line %d\n", yylineno);
		}
		ntoken = yylex();
	}
	return 0;
}

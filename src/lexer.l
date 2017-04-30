/* Lexer.l
 *
 * Lexer.l contains the lexical rules to tokenize the lisp
 * files correctly.
 *
 * Software Systems Spring 2017 - Olin College
 * Eccentric Eucalyptus
 *
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h" // generated via yacc -d
%}

%option noyywrap

%%

let                             {yylval.keyword = strdup(yytext); return LET_KW;}
[0-9]+(\.[0-9]+)?([eE][0-9]+)?  {yylval.f = atof(yytext); return NUM;}
[+()*-/]                        {return yytext[0];} 
[ \t\f\v\n]                     { ; }
[A-Za-z][A-Za-z0-9]*            {yylval.name = strdup(yytext); return VNAME;} 

%%

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h" // generated via yacc -d
%}

%option noyywrap

%%

let                             {yylval.keyword = strdup(yytext); return LET_KW;}
defun                           {yylval.keyword = strdup(yytext); return DEFUN_KW;}
[0-9]+(\.[0-9]+)?([eE][0-9]+)?  {yylval.f = atof(yytext); return NUM;}
[+()*-/]                        {return yytext[0];} 
[ \t\f\v\n]                     { ; }
[A-Za-z][A-Za-z0-9]*            {yylval.name = strdup(yytext); return NAME;} 

%%

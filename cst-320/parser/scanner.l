%{
//*********************************************************
// filename: scanner.l
// purpose: scanner definition file for CST320 Lab 3.          
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/23/20

#include "tokens.h"
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

OP              [\+\-\*\/]
%%
"("             return '(';          
")"             return ')';
"["             return '[';
"]"             return ']';
";"             return ';';
"="             return '=';
{OP}            return OP;
"end"           return CLOSE;
"while"         return WHILE;

([A-Z]|[a-z])([A-Z]|[a-z]|[0-9])*   return VAR;
[0-9]+                              return NUM;

"{".*"}"        {}
" "             {}
\t              {}
\n              {}
\r              {}

.               return JUNK;
%%

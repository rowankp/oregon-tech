//**********************************************************
// filename: lex.h
// purpose: defines global symbols used the the flex 
//          generated lexer for CST320 Lab 3.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/23/20

#pragma once
#include <iostream>

int yylex();

extern char *yytext;
extern int yylineno;
extern int yynerrs;
extern FILE *yyin;

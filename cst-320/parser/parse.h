//**********************************************************
// filename: parse.h
// purpose: declares parse routines for top-down 
//          recursive-descent parser for use in CST320 Lab3.
//          The following functions are for finding 
//          non-terminals that are part of the calc grammar.
//          Functions return true if the non-terminal was 
//          found, false otherwise.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/23/20 

#pragma once
bool FindPROG();
bool FindSTMTS();
bool FindSTMT();
bool FindEXPR();
bool FindOP();

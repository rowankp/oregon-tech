//**********************************************************
// filename: utils.h
// purpose: declares utilities useful for a top-down 
//          recursive-descent parser.
// author: Rowan Parker
// date: 01/23/20

#pragma once
#include <iostream>
#include <string>

void Error(std::string expecting);
int PeekToken();
int AdvanceToken();
int GetToken();
int UngetToken(int token);

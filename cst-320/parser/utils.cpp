//**********************************************************
// filename: utils.cpp
// purpose: implementation of utilities useful for top-down 
//          recursive-descent parsers
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/23/20

#include <iostream>
#include <string.h>
#include "lex.h"
#include "utils.h"

using std::cout;

// keep track of the last peeked token
static int g_token = -1;

//**********************************************************
// method: Error
// parameters: string
// purpose: print an error in a standard form.
void Error(std::string expecting)
{
    if (yytext != NULL && strlen(yytext) > 0)
    {
        cout << "Found '" << yytext << "' when expecting a " << expecting;
    }
    else
    {
        cout << "Found End-Of-File when expecting a " << expecting;
    }

    std::cout << " in line " << yylineno << std::endl;
}

//**********************************************************
// method: GetToken
// parameters: none
// purpose: read the next token from the input.
int GetToken()
{
    int token = g_token;
    
    if (token < 0) 
    {
        token = yylex();
    }
    
    g_token = -1;

    return token;
}

//**********************************************************
// method: UngetToken
// parameters: int
// purpose: put the last-read token back into the input. 
//          Only works as a one-level undo, not an N-level 
//          undo.
int UngetToken(int token)
{
    g_token = token;

    return g_token;
}

//**********************************************************
// method: PeekToken
// parameters: none
// purpose: look at the next token without consuming it
int PeekToken()
{
    if (g_token < 0) 
    {
        g_token = yylex();
    }

    return g_token;
}

//**********************************************************
// method: AdvanceToken
// parameters: none
// purpose: read the next token from the input
int AdvanceToken()
{
    g_token = yylex();

    return g_token;
}

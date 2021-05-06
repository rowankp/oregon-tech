//**********************************************************
// filename: parse.cpp
// purpose: implementation of functions for finding
//          non-terminals that are part of the calc grammar
//          defined in CST320 Lab 3. Starting point for
//          top-down recursive-descent parser.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/23/20

#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <unordered_set>
using std::unordered_set;

static unordered_set<int> STMT_set = {VAR, WHILE, '['};
static unordered_set<int> EXPR_set = {VAR, NUM, OP};
static unordered_set<int> ERROR_set = {';', '[', ']', CLOSE, 0}; 
//**********************************************************
// method: IsIn
// parameters: unordered_set<int> reference, int
// purpose: searches a set for a value. If found, returns
//          true. If not found, returns false.
static bool IsIn(unordered_set<int>& set, int value)
{
    auto found = set.find(value);
    if (found != set.end()) return true;
    return false;
}

//**********************************************************
// method: FindPROG
// paremeters: none
// purpose: searches for a PROG non-terminal.
// productions: PROG -> STMTS end
bool FindPROG()
{
     // search for STMTS
    FindSTMTS();
    
    // snag current token   
    int token = PeekToken();

    // search for end
    if (token != CLOSE)
    {
        Error("end");
        return false;
    }

    return true;
}

//**********************************************************
// method: FindSTMTS
// parameters: none
// purpose: searches for a STMTS non-terminal.
// productions: STMTS -> STMT STMTS
//                    -> lamda
bool FindSTMTS()
{
    int token = PeekToken();

    // check STMT first plus set
    while (IsIn(STMT_set, token))
    {
        // loop while finding valid STMTS
        while (FindSTMT()) { }

        // loop breaks due to invalid STMT, get error token
        token = PeekToken();

        // loop until error sync point
        while (!IsIn(ERROR_set, token))
        {
            token = AdvanceToken();
        }      
        
        // next token after end, [, or ] should be a valid
        // statement. grab the next token and enter outer
        // loop again 
        if (token != CLOSE && token != '[' && token != ']')
        {
            token = AdvanceToken();
        }
    }

    return true;
}

//**********************************************************
// method: FindSTMT
// parameters: none
// purpose: searches for a STMT non-terminal.
// productions: STMT -> var = EXPR;
//                   -> while ( EXPR) STMT
//                   -> [ STMTS ]
bool FindSTMT()
{
    // snag the current token
    int token = PeekToken();

    // check if in first plus set
    if (!IsIn(STMT_set, token)) return false;   

    // STMT -> var = EXPR;
    if (token == VAR)
    {
        // advance and find =
        token = AdvanceToken();
        if (token != '=') 
        { 
            Error("'='");
            return false; 
        }
        
        // advance and find EXPR
        token = AdvanceToken();
        if (!FindEXPR()) 
        {
            Error("EXPR");
            return false;
        }

        // find ;
        token = PeekToken();
        if (token != ';') 
        { 
            Error("';'");
            return false; 
        }
        
        // var = EXPR found, loop for next token
        AdvanceToken();
    }
    // while ( EXPR ) STMT
    else if (token == WHILE)
    {
        // advance and find {
        token = AdvanceToken();
        if (token != '(') 
        {
            Error("'('");
            return false;
        }

        // advance and find EXPR
        token = AdvanceToken();
        if (!FindEXPR())
        {
            Error("EXPR");
            return false;
        }

        // advance and find )
        token = PeekToken();
        if (token != ')')
        {
            Error("')'");
            return false;
        }

        // advance and find STMT
        token = AdvanceToken();
        if (!FindSTMT())
        {

            return false;
        }
        
        // while ( EXPR ) STMT found
       // AdvanceToken();
    }
    // [ STMTS ]
    else if (token == '[')
    {
        // advance and find STMTS
        token = AdvanceToken();
        if (!FindSTMTS())
        {
            return false;
        }

        //  and find ]
        token = PeekToken();
        if (token != ']') 
        {
            Error("']'");
            return false;
         }
        
        // [ STMTS ] found, advance scanner
        AdvanceToken();
    }

    cout << "Found a statement" << endl;
    return true; 
}

//*********************************************************
// method: FindEXPR
// parameters: none
// purpose: searches for a EXPR non-terminal.
// productions: EXPR -> OP EXPR EXPR
//                   -> num
//                   -> var
bool FindEXPR()
{
    int token = PeekToken();

    if (!IsIn(EXPR_set, token)) return false;

    // EXPR -> OP EXPR EXPR
    if (FindOP())
    {
        // advance and find EXPR
        AdvanceToken();
        if (!FindEXPR())
        {
            return false;
        }

        // advance and find EXPR
        // AdvanceToken();
        if (!FindEXPR())
        {
            return false;
        }

        // OP EXPR EXPR found
     }
    // EXPR -> num
    else if (token == NUM)
    {
        // advance and return
        AdvanceToken();
    }
    // EXPR -> var
    else if (token == VAR) 
    {
        // advance and return
        AdvanceToken();
    }
    
    return true;
}

//**********************************************************
// method: FindOP
// parameters: none
// purpose: searches for a OP non-terminal.
// productions: OP -> + | - | + | /
bool FindOP()
{
   return (PeekToken() == OP);
}

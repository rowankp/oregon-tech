%{
//*********************************************************
// Filename: pascal.l
// Purpose: scanner definition
// Author: Rowan Parker (rowan.parker@oit.edu)
// Date: 01/07/2020

#include "astnodes.h"
#include "cSymbolTable.h"
#include "pascalparse.h"
#include "lex.h"
#include <string>
#include <cctype>
#include <algorithm>

// comment out the other line to generate debug info
#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);
int ProcessIdentifier(std::string);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno

%%
":"             DO_RETURN(':');
"("             DO_RETURN('(');          
")"             DO_RETURN(')');
"["             DO_RETURN('[');
"]"             DO_RETURN(']');
";"             DO_RETURN(';');
","             DO_RETURN(',');
"."             DO_RETURN('.');
"+"             DO_RETURN('+');
"-"             DO_RETURN('-');
"*"             DO_RETURN('*');
"/"             DO_RETURN('/');
"="             DO_RETURN('=');
"^"             DO_RETURN('^');
"<"             DO_RETURN('<');
">"             DO_RETURN('>');

"<="            DO_RETURN(LE);
">="            DO_RETURN(GE);
":="            DO_RETURN(ASSIGN);
"<>"            DO_RETURN(NOT_EQUAL);

([A-Z]|[a-z])([A-Za-z0-9])*         DO_RETURN(ProcessIdentifier(yytext));

[0-9]+                              {
                                        yylval.int_val = atoi(yytext);
                                        DO_RETURN(INT_VAL);
                                    }
[0-9]+(\.)?[0-9]+|[0-9]             {
                                        yylval.real_val = std::stod(yytext);
                                        DO_RETURN(REAL_VAL);
                                    }
"{".*"}"        {}
" "             {}
\t              {}
\n              {}
\r              {}

.        DO_RETURN(JUNK_TOKEN);
%%

//*********************************************************
// Function: Return
// Parameters: int
// Purpose: allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

//*********************************************************
// Function: ProcessIdentifier
// Parameters: none
// Purpose: copies yytext, transforms to lower case, then 
//          inserts the symbol in the current scope
int ProcessIdentifier(std::string identifier)
{
    std::string key = identifier;

    // transform key to lowercase
    std::transform(key.begin(), key.end(), key.begin(), tolower);
    
    // search for symbol
    yylval.symbol = symbolTable.GlobalLookup(key);
    
    // if not found, insert symbol
    if (yylval.symbol == nullptr)
    {
        yylval.symbol = new cSymbol(key);
    }

    // test for is type
    if (yylval.symbol != nullptr)
    { 
        if (yylval.symbol->IsType())
        {   
            return TYPE_ID;  
        }     
        else
        {
             return yylval.symbol->GetTokenType();
        }
    }
    
    return IDENTIFIER;
}

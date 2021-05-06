//**********************************************************
// Filename: cSymbolTable.h
// Purpose: cSymbolTable class declaration.
// Author: Rowan Parker
// Date: 01/17/2019

#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "cSymbol.h"
#include "pascalparse.h"
#include "cBaseTypeNode.h"

using std::unordered_map;
using std::vector;
using std::string;

class cSymbolTable
{
    public:
        //**************************************************
        // constructor
        cSymbolTable() : m_table(), m_scope(0)
        { 
            InitializeSymbolTable(); 
        }

        //**************************************************
        // creates new map to hold cSymbols and increments 
        // that scope counter
        void IncreaseScope()
        {
            m_table.push_back(unordered_map<string, cSymbol *>());
            ++m_scope;
        } 

        //**************************************************
        //  pops the last map of cSymbols and decremeants 
        //  the scope counter.
        void DecreaseScope()
        {
            m_table.pop_back();
            --m_scope;
        }

        //**************************************************
        // inserts a cSymbol into the current scope.
        cSymbol * Insert(string key)
        {
            cSymbol * symbol = new cSymbol(key);
            
            m_table.back().insert({key, symbol}); 

            // return symbol
            return symbol;
        }
        
        //**************************************************
        // method: Insert
        // parameters: cSymbol *
        // purpose: insert a keyword into the global scope
        void Insert(cSymbol * symbol)
        {
            m_table[m_scope].insert({symbol->GetName(), symbol});
        }

        //**************************************************
        // finds a cSymbol based on name. First searches 
        // current scope, then searches through scopes 
        // sequentially. Returns the address of the cSymbol. 
        // If not found, returns nullptr.
        cSymbol * GlobalLookup(string key)
        {
           cSymbol * symbol = nullptr;

           // preform local lookup
           symbol = LocalLookup(key);

           // if not found locally, begin global search
           if (symbol == nullptr)
           {
               int current_scope = m_scope;
                
               // begin looping through scopes
               while (current_scope >= 0 && symbol == nullptr)
               {
                   auto iter = m_table[current_scope].find(key);

                   // if found, assign symbol
                   if (iter != m_table[m_scope].end())
                   {
                       symbol = iter->second;
                   }
                   // else, decrease scope
                   else
                   {
                       --current_scope;
                   }
                }        
           }
          
            return symbol;
        }

        //**************************************************
        // finds a cSymbol based on name. Only searches 
        // current scope. Returns the address of the cSymbol.
        // If not found, returns nullptr.
        cSymbol * LocalLookup(string key)
        {                     
            cSymbol * symbol = nullptr;
            
            auto iter = m_table[m_scope].find(key);

            // if found, assign symbol
            if (iter != m_table[m_scope].end())
            {
                symbol = iter->second;
            }
                        
            return symbol;
        }

    private:
        vector<unordered_map<string, cSymbol *>> m_table;
        int m_scope;

        //*************************************************
        // creates a global scope in symbol table and 
        // inserts the keywords
        void InitializeSymbolTable()
        {
            // create global scope
            m_table.push_back(unordered_map<string, cSymbol *>());

            cSymbol * keyword = nullptr;

            // integer, size = 4, not float
            keyword = new cSymbol("integer", -1, true);
            keyword->SetTokenType(INTEGER);
            keyword->SetDecl(new cBaseTypeNode("integer", 4, false));
            Insert(keyword);

            // real, size = 8, is float
            keyword = new cSymbol("real", -1, true);            
            keyword->SetTokenType(REAL);
            keyword->SetDecl(new cBaseTypeNode("real", 8, true));
            Insert(keyword);

            // char, size = 1, not float
            keyword = new cSymbol("char", -1, true);
            keyword->SetTokenType(CHAR);
            keyword->SetDecl(new cBaseTypeNode("char", 1, false));
            Insert(keyword);

            // program
            keyword = new cSymbol("program", PROGRAM);
            Insert(keyword);

            // procedure
            keyword = new cSymbol("procedure", PROCEDURE);
            Insert(keyword);

            // function
            keyword = new cSymbol("function", FUNCTION);
            Insert(keyword);

            // begin
            keyword = new cSymbol("begin", OPEN);
            Insert(keyword);

            // end
            keyword = new cSymbol("end", CLOSE);
            Insert(keyword);

            // if
            keyword = new cSymbol("if", IF);
            Insert(keyword);

            // then
            keyword = new cSymbol("then", THEN);
            Insert(keyword);

            // else
            keyword = new cSymbol("else", ELSE);
            Insert(keyword);

            // while
            keyword = new cSymbol("while", WHILE);
            Insert(keyword);

            // repeat
            keyword = new cSymbol("repeat", REPEAT);
            Insert(keyword);

            // until
            keyword = new cSymbol("until", UNTIL);
            Insert(keyword);

            // for
            keyword = new cSymbol("for", FOR);
            Insert(keyword);

            // do
            keyword = new cSymbol("do", DO);
            Insert(keyword);

            // to
            keyword = new cSymbol("to", TO);
            Insert(keyword);

            // downto
            keyword = new cSymbol("downto", DOWNTO);
            Insert(keyword);

            // forward
            keyword = new cSymbol("forward", FORWARD);
            Insert(keyword);

            // const
            keyword = new cSymbol("const", CONST);
            Insert(keyword);

            // type
            keyword = new cSymbol("type", TYPE);
            Insert(keyword);

            // var
            keyword = new cSymbol("var", VAR);
            Insert(keyword);

            // array
            keyword = new cSymbol("array", ARRAY);
            Insert(keyword);

            // record
            keyword = new cSymbol("record", RECORD);
            Insert(keyword);

            // of
            keyword = new cSymbol("of", OF);
            Insert(keyword);

            // nil
            keyword = new cSymbol("nil", NIL);
            Insert(keyword);

            // write
            keyword = new cSymbol("write", WRITE);
            Insert(keyword);

            // or
            keyword = new cSymbol("or", OR);
            Insert(keyword);

            // div
            keyword = new cSymbol("div", DIV);
            Insert(keyword);

            // mod
            keyword = new cSymbol("mod", MOD);
            Insert(keyword);

            // and
            keyword = new cSymbol("and", AND);
            Insert(keyword);

            // not
            keyword = new cSymbol("not", NOT);
            Insert(keyword);
       }
};

extern cSymbolTable symbolTable;

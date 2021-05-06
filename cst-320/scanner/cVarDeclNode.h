//**********************************************************
// filename: cVarDeclNode
// purpose: defines a base class for all var declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cSymbolTable.h"
#include "cDeclNode.h"
#include "cBaseTypeNode.h"
#include "cSymbol.h"
#include <string>
using std::to_string;

class cVarDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cVarDeclNode(cDeclNode * type, cSymbol * symbol) : cDeclNode() 
        {
            std::string name = symbol->GetName();

            if (type != nullptr && symbol != nullptr)
            {  
                if (symbolTable.GlobalLookup(name) == symbol)
                {
                    if (symbolTable.LocalLookup(name) != symbol)
                    {
                        symbol = new cSymbol(name);
                    }
                    else
                    {
                        SemanticParseError("Symbol " + name + " already exists in current scope ");
                    }
                }

                symbol->SetDecl(this);
                symbolTable.Insert(symbol);
                
                AddChild(type);
                AddChild(symbol);    
            }
        }
       
       //**************************************************
       // m_type accesor
       cDeclNode * GetType() { return dynamic_cast<cDeclNode *>(GetChild(TYPE)); }
       
       //***************************************************
       // m_symbol accessor
       cSymbol * GetSymbol() { return dynamic_cast<cSymbol *>(GetChild(SYMBOL)); }

       //***************************************************
       virtual string GetName() { return GetSymbol()->GetName(); }

       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "var_decl"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

       virtual string AttributesToString() 
       { 
           return " size=\"" + to_string(GetSize()) + 
                  "\" offset=\"" + to_string(GetOffset()) + "\"";
       }

    protected:
       const int TYPE = 0;
       const int SYMBOL = 1;
};

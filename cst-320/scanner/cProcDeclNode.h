//**********************************************************
// filename: cProcDeclNode
// purpose: defines an ast node for  procedure declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/07/2020

#pragma once
#include "cDeclNode.h"
#include "cVarDeclsNode.h"
#include "cBlockNode.h"
#include "cSymbolTable.h"

class cProcDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cProcDeclNode(cSymbol * symbol) : cDeclNode() 
        {
            if (symbol != nullptr)
            {
                std::string name = symbol->GetName();

                if(symbolTable.GlobalLookup(name) == symbol)
                {
                    if (symbolTable.LocalLookup(name) != symbol)
                    {
                        symbol = new cSymbol(symbol->GetName());
                    }
                    else
                    {
                        SemanticParseError("Symbol " + name + " already exists in scope ");
                    }
                }

                symbol->SetDecl(this);
                symbolTable.Insert(symbol);
                AddChild(symbol);
            }
        }

       //***************************************************
       // add var decls
       void AddParamSpec(cVarDeclsNode * vars) { AddChild(vars); }

       //***************************************************
       // add block node
       void AddBlock(cBlockNode * block) { AddChild(block); }

       //***************************************************
       cBlockNode * GetBlock()
       {
           return dynamic_cast<cBlockNode *>(GetChild(BLOCK));
       }

       //***************************************************
       cVarDeclsNode * GetParamSpec() 
       {
           return dynamic_cast<cVarDeclsNode *>(GetChild(PARAM));
       }

       //***************************************************
       int GetNumParams()
       {
           if (GetParamSpec() == nullptr) { return 0; }

           return GetParamSpec()->GetNumDecls();
       }

       //***************************************************
       virtual cDeclNode * GetType() { return this; }

       //***************************************************
       virtual string GetName()
       {
           return dynamic_cast<cSymbol *>(GetChild(NAME))->GetName();
       }

       //***************************************************
       // return is proc
       virtual bool IsProc() { return true; }

       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "proc"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
       const int NAME = 0;
       const int PARAM = 1;
       const int BLOCK = 2;
};

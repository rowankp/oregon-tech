//**********************************************************
// filename: cConstDeclNode
// purpose: defines an ast node for const declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/09/2020

#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"
#include "cExprNode.h"

class cConstDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cConstDeclNode(cSymbol * name, cExprNode * expr) : cDeclNode() 
        {
            if (name != nullptr && expr != nullptr)
            {  
                if(symbolTable.GlobalLookup(name->GetName()) == name)
                {
                   name = new cSymbol(name->GetName());
                }

                symbolTable.Insert(name);
                name->SetDecl(this);

                AddChild(name);
                AddChild(expr);    
            }
        }
     
       //***************************************************
       virtual string GetName() 
       { 
           return dynamic_cast<cSymbol *>(GetChild(NAME))->GetName(); 
       }
        
       //***************************************************
       virtual cDeclNode * GetType() 
       { 
           return dynamic_cast<cSymbol *>(GetChild(NAME))->GetDecl();
       }

       //***************************************************
       // is int?
       virtual bool IsInt() { return true; }

       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "const_decl"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

       private:
       const int NAME = 0;
};

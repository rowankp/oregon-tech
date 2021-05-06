//**********************************************************
// filename: cRecordDeclNode
// purpose: defines an ast node for record declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"

class cRecordDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cRecordDeclNode(cSymbol * name, cDeclsNode * decls) : cDeclNode() 
        {
            if (name != nullptr && decls != nullptr)
            {  
                if(symbolTable.GlobalLookup(name->GetName()) == name)
                {
                   name = new cSymbol(name->GetName());
                }

                symbolTable.Insert(name);
                name->SetDecl(this);
                name->SetIsType(true);

                AddChild(name);
                AddChild(decls);    
            }
        }
       
       //***************************************************
       virtual cDeclNode * GetType() { return this; }

       //***************************************************
       virtual string GetName() 
       {
           return dynamic_cast<cSymbol *>(GetChild(0))->GetName();
       }
           
       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "record"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }
};

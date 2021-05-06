//**********************************************************
// filename: cIdListNode.h
// purpose: defines an AST node that stores a list of 
//          cSymbol pointers.
// author: Rowan Parker
// date: 02/02/2020

#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"

class cIdListNode : public cAstNode
{
    public:
    //******************************************************
    // constructor
    cIdListNode(cSymbol * symbol = nullptr) : cAstNode()
    {
        if (symbol != nullptr)
        {
           AddChild(symbol); 
        }
    }

    //******************************************************
    // adds a child
    void AddId(cSymbol * symbol)
    {
        if (symbol != nullptr)
        {
            AddChild(symbol);
        }
    }

    //******************************************************
    // returns a child
    cSymbol * GetId(int id) { return dynamic_cast<cSymbol *>(GetChild(id)); }

    //******************************************************
    // returns the number of child
    int GetNumId() { return NumChildren(); }

    //******************************************************
    // returns a string with the node type
    virtual string NodeType() { return "idList"; }

    //******************************************************
    // defines the visit method for this node
    virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }     
};

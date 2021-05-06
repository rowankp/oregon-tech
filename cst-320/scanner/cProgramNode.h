//**********************************************************
// filename: cProgramNode.h
// purpose: defines AST node for a lang program
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cSymbol.h"
#include "cBlockNode.h"

class cProgramNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cProgramNode(cSymbol *name, cBlockNode *block) : cAstNode()
        {
            AddChild(name);
            AddChild(block);

            symbolTable.Insert(name);
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("program"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

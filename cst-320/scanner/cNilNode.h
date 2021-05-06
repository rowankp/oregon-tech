//**********************************************************
// filename: cNilNode.h
// purpose: degines an AST for a no-op statement.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"

class cNilNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cNilNode() : cStmtNode() { }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("NIL"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

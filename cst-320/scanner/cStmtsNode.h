//**********************************************************
// filename: cStmtsNode.h
// purpose: defines AST node that represents a list of 
//          statements.
// author: Rowan Parker (rowan.parker@.oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"

class cStmtsNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cStmtsNode(cStmtNode *stmt) : cAstNode()
        {
            AddChild(stmt);
        }

        //**************************************************
        // add a child
        void AddNode(cStmtNode * stmt)
        {
            AddChild(stmt);
        }

        //**************************************************
        // return a string with the node type
        virtual string NodeType() { return string("stmts"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

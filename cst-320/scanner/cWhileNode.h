//**********************************************************
// filename: cWhileNode.h
// purpose: defines an AST node for a while loop.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cWhileNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cWhileNode(cExprNode * expr, cStmtNode * stmt) : cStmtNode() 
        {
            if (expr != nullptr)
            {
                AddChild(expr);
            }

            if (stmt != nullptr)
            {
                AddChild(stmt);
            }
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("while"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

//**********************************************************
// filename: cIfNode.h
// purpose: defines an AST node for an if statement.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/06/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"

class cIfNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cIfNode(cExprNode * cond, cStmtNode * stmt1, cStmtNode * stmt2 = nullptr) 
            : cStmtNode() 
        {
            if (cond != nullptr)
            {
                AddChild(cond);
            }

            if (stmt1 != nullptr)
            {
                AddChild(stmt1);
            }

            if (stmt2 != nullptr)
            {
                AddChild(stmt2);
            }
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("if"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

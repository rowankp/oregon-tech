//**********************************************************
// filename: cUnaryExprNode.h
// purpose: defines an AST node for unary expressions.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cUnaryExprNode : public cExprNode
{
    public:
        //**************************************************
        // constructor
        cUnaryExprNode(cOpNode * op, cExprNode * expr) : cExprNode()
        {

            if (op != nullptr)
            {
                AddChild(op);
            }

            if (expr != nullptr)
            {
                AddChild(expr);
            }
        }

        //**************************************************
        // returns unary operator
        virtual cDeclNode * GetType()
        {
            return dynamic_cast<cExprNode *>(GetChild(1))->GetType();
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("unaryExpr"); }

        //**************************************************
        // defines the visit method for the node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

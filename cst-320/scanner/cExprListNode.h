//**********************************************************
// filename: cExprListNode.h
// purpose: defines AST node for actual parameters passed
//          to a function.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cExprNode.h"

class cExprListNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cExprListNode(cExprNode *param = nullptr) : cAstNode()
        {
            if (param != nullptr) AddChild(param);
        }
        
        //**************************************************
        // adds a child
        void AddNode(cExprNode * expr)
        {
            if (expr != nullptr)
            {
                AddChild(expr);
            }
        }

        //**************************************************
        cExprNode * GetParam(int index) 
        {
            return dynamic_cast<cExprNode *>(GetChild(index));
        }

        //**************************************************
        // return num params
        int GetNumParams()
        {
            return NumChildren();
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("exprList"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

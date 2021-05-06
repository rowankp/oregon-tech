//**********************************************************
// filename: cAssignNode.h
// purpose: defines an AST node for an assignment statement.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprNode.h"
#include "cVarExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cAssignNode(cVarExprNode * var, cExprNode * expr) : cStmtNode() 
        {
            AddChild(var);
            AddChild(expr);
        }

        //**************************************************
        // get lval
        cVarExprNode * GetLVal()
        {
            return dynamic_cast<cVarExprNode *>(GetChild(LVAL));
        }

        //**************************************************
        // get rval
        cExprNode * GetRVal()
        {
            return dynamic_cast<cExprNode *>(GetChild(RVAL));
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("assign"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    private:
        const int LVAL = 0;
        const int RVAL = 1;
};

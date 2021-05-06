//**********************************************************
// filename: cWriteNode.h
// purpose: defines AST node for WRITE statements.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"
#include "cExprListNode.h"

class cWriteNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cWriteNode(cExprListNode *exprList) : cStmtNode()
        {
            AddChild(exprList);
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("WRITE"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

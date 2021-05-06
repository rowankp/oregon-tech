//**********************************************************
// filename: cCompoundStmtNode.h
// purpose: defines AST node for compound statements.
// author: Rowan Parker (rowan.parker@.oit.edu)
// date: 02/06/2020

#pragma once
#include "cAstNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

class cCompoundStmtNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cCompoundStmtNode(cStmtsNode * stmt = nullptr) : cStmtNode()
        {
            if (stmt != nullptr)
            {
                AddAllChildren(stmt);
            }
        }

        //**************************************************
        // cosntructor
        cCompoundStmtNode(cStmtNode * stmt = nullptr) : cStmtNode()
        {
            if (stmt != nullptr)
            {
                AddChild(stmt);
            }
        }

        //**************************************************
        // add a child
        void AddNode(cStmtNode * stmt)
        {
            if (stmt != nullptr)
            {
                 AddChild(stmt);
            }
        }

        //**************************************************
        // return a string with the node type
        virtual string NodeType() { return string("compound"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

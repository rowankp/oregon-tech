//**********************************************************
// filename: cIntExprNode.h
// purpose: defines an AST node for an integer constant 
//          (literals). Inherits from cExprNode so that 
//          integer constants can be used anywhere 
//          expressions are used.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cExprNode.h"

class cIntExprNode : public cExprNode
{
    public:
        //**************************************************
        // constructor
        cIntExprNode(int value) : cExprNode()
        {
            m_value = value;
        }

        virtual bool IsCharCompatible()
        {
            if (m_value < 127 && m_value > -128) { return true; }
            return false;
        }

        // returns integer type
        virtual cDeclNode * GetType()
        {
            return symbolTable.GlobalLookup("integer")->GetDecl();
        }

        //**************************************************
        // returns a string with the attributes of the node
        virtual string AttributesToString()
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("INTEGER"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        int m_value;
};

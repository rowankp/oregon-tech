//**********************************************************
// filename: cRealExprNode.h
// purpose: defines an AST node for real constants
//          (literals). Inherits from cExprNode so that real
//          constants can be used anywhere expressions are 
//          used.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cAstNode.h"
#include "cExprNode.h"

class cRealExprNode : public cExprNode
{
    public:
        //**************************************************
        // constructor
        cRealExprNode(double value) : cExprNode()
        {
            m_value = value;
        }

        //**************************************************
        // returns real type
        virtual cDeclNode * GetType()
        {
            return symbolTable.GlobalLookup("real")->GetDecl();
        }

        //**************************************************
        // returns a string with the attributes of the node
        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        
        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("REAL"); }
        
        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
   
    protected:
        double m_value;
};

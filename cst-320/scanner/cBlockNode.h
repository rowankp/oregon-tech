//**********************************************************
// filename: cBlockNode.h
// purpose: defines an AST node for a block of code
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "cDeclsNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

class cBlockNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cBlockNode(cDeclsNode * decls, cStmtsNode * statements) : cStmtNode()
        {
            AddChild(decls);
            AddChild(statements);
        }

        int GetSize() { return m_size; }
        
        void SetSize(int size) { m_size = size; }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("block"); }

        virtual string AttributesToString()
        {
            return " size=\"" + std::to_string(m_size) + "\"";
        }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
        int m_size = 0;
};

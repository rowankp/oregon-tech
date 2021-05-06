//**********************************************************
// filename: cRangeDeclNode.h
// purpose: defines an ast node for range declarations
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/09/2020

#pragma once
#include "cDeclNode.h"

class cRangeDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cRangeDeclNode(int start, int end) : cDeclNode() 
        {
            m_start = start;
            m_end = end;
        }

        //**************************************************
        int GetStart() { return m_start; }

        //**************************************************
        int GetEnd() { return m_end; }

        //**************************************************
        virtual string GetName() { return ""; }

        //**************************************************
        virtual cDeclNode * GetType () { return this; }

        //**************************************************
        // returns a string with the attributes of the node
        virtual string AttributesToString()
        {
            return " start=\"" + std::to_string( m_start) +
                   "\" end=\"" + std::to_string(m_end) + "\"";
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("range"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    protected:
        int m_start = 0;
        int m_end = 0;
};

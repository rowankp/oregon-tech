//**********************************************************
// filename: cOpNode.h
// purpose: class for an operator (e.g. + - etc.)
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include "pascalparse.h"

class cOpNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cOpNode(int op) : cAstNode() { m_op = op; }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return "op"; }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
       
        //**************************************************
        // returns a string with the attributes of the node
        virtual string AttributesToString()   
        { 
            string result(" value=\"");

            switch (m_op)
            {
                case OR:
                    result += "OR";
                    break;
                case AND:
                    result += "AND";
                    break;
                case MOD:
                    result += "MOD";
                    break;
                case DIV:
                    result += "DIV";
                    break;
                case NOT:
                    result += "NOT";
                    break;
                case LE:
                    result += "LE";
                    break;
                case GE:
                    result += "GE";
                    break;
                case NOT_EQUAL:
                    result += "NE";
                    break;
                case '<':
                    result += "LT";
                    break;
                case '>':
                    result += "GT";
                    break;
                default:
                    result += (char)m_op;
                    break;
            }

            result += "\"";

            return result;
        }

    protected:
        int m_op;      // the operand
};


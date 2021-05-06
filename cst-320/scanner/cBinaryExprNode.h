//**********************************************************
// filename: cBinaryExprNode.h
// purpose: defines an AST node for binary expressions.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cAstNode.h"
#include "cExprNode.h"
#include "cOpNode.h"

class cBinaryExprNode : public cExprNode
{
    public:

        //**************************************************
        // constructor
        cBinaryExprNode(cExprNode * expr1, cOpNode * op, cExprNode * expr2) 
            : cExprNode()
        {
            AddChild(expr1);
            AddChild(op);
            AddChild(expr2);
        }

        //**************************************************
        // returns the type of the expression
        virtual cDeclNode * GetType()
        {
            cDeclNode * expr1 = dynamic_cast<cExprNode *>(GetChild(EXPR1))->GetType();
            cDeclNode * expr2 = dynamic_cast<cExprNode *>(GetChild(EXPR2))->GetType();

                if (expr1->IsType())                          { return expr1; }
                else if (expr2->IsType())                     { return expr2; }
                else if (expr1->IsReal() && expr2->IsReal())  { return expr1; }
                else if (expr1->IsReal() && expr2->IsInt())   { return expr1; }
                else if (expr1->IsReal() && expr2->IsChar())  { return expr1; }
                else if (expr1->IsInt()  && expr2->IsReal())  { return expr2; }
                else if (expr1->IsInt()  && expr2->IsInt())   { return expr1; }
                else if (expr1->IsInt()  && expr2->IsChar())  { return expr1; }
                else if (expr1->IsChar() && expr2->IsReal())  { return expr2; }
                else if (expr1->IsChar() && expr2->IsInt())   { return expr2; }
                else if (expr1->IsChar() && expr2->IsChar())  { return expr1; }
                else { return expr1; }
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("expr"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        
    protected:
        const int EXPR1 = 0;
        const int EXPR2 = 2;
};

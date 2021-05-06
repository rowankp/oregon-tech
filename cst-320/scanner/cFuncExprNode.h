//**********************************************************
// filename: cFuncExprNode.h
// purpose: defines an ast node for a function call.
// author: Rowan Parker
// date: 02/09/2020

#pragma once
#include "cExprNode.h"
#include "cSymbol.h"

class cFuncExprNode : public cExprNode
{
    public:
    //******************************************************
    // constructor 
    cFuncExprNode(cSymbol * symbol, cExprListNode * expr) : cExprNode()
    {
        AddChild(symbol);
        AddChild(expr);
    }
   
    //******************************************************
    // return the func symbol
    cSymbol * GetFunc()
    {
        return dynamic_cast<cSymbol *>(GetChild(TYPE));
    }

    //******************************************************
    // return the expr
    cExprListNode * GetExpr()
    {
        return dynamic_cast<cExprListNode *>(GetChild(EXPR));
    }
 
    //****************************************************** 
    cExprNode * GetParam(int index)
    {
        return GetExpr()->GetParam(index);
    } 

    //******************************************************
    int GetNumParams()
    {
        return GetExpr()->GetNumParams();
    }

    //******************************************************
    void SetSize(int size) { m_size = size; }

    //******************************************************
    // returns the type of the expression
    virtual cDeclNode * GetType()
    {
        return GetFunc()->GetDecl()->GetType();
    }

    //******************************************************
    virtual string AttributesToString()
    {
        return " paramSize=\"" + to_string(m_size) + "\"";
    }

    //******************************************************
    // returns the type of the node
    virtual string NodeType() { return "funcCall"; }

    //******************************************************
    // defines the visit method for this node
    virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    protected:
    const int TYPE = 0;
    const int EXPR = 1;
    int m_size = 0;
};

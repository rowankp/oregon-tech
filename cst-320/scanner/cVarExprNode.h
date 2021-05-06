//**********************************************************
// filename: cVarExprNode.h
// purpose: class definition for cVarExprNode.
// author: Rowan Parker
// date: 02/03/2020

#pragma once
#include "cExprNode.h"
#include "cExprListNode.h"
#include "cSymbol.h"
#include <string>
using std::to_string;

class cVarExprNode : public cExprNode
{
    public:
    //******************************************************
    // constructor 
    cVarExprNode(cSymbol * symbol) : cExprNode()
    {
        AddChild(symbol);
    }

    //******************************************************
    // add symbol child
    void AddSymbol(cSymbol * symbol)
    {
        AddChild(symbol);
    }

    //******************************************************
    // add expr list
    void AddExprList(cExprListNode * expr)
    {
        AddChild(expr);
    }

    //******************************************************
    // get symbol
    cSymbol * GetSymbol()
    {
        return dynamic_cast<cSymbol *>(GetChild(SYMBOL));
    }
    
    //******************************************************
    void SetSize(int size) { m_size = size; }

    //******************************************************
    void SetOffset(int offset) { m_offset = offset; }

    //******************************************************
    void AddRowSize(int size) { m_rowsizes.push_back(size); }

    //******************************************************
    void AddStartIndex(int start) { m_startindexes.push_back(start); }

    //******************************************************
    // returns the decl attached to the symbol
    virtual cDeclNode * GetType()
    {
        if (GetChild(EXPR) != nullptr)
        {
           return dynamic_cast<cSymbol *>(GetChild(SYMBOL))->GetDecl()->GetType()->GetType();
        }
        else
        {
            return dynamic_cast<cSymbol *>(GetChild(SYMBOL))->GetDecl();
        }       
    }

    //******************************************************
    virtual string AttributesToString()
    { 
        string ret = " size=\"" + to_string(m_size) +
                     "\" offset=\"" + to_string(m_offset) + "\"";

        if (m_rowsizes.size() != 0)
        {
            ret += " rowsizes=" + ElementsToString(m_rowsizes);
            ret += " startindexes=" + ElementsToString(m_startindexes);
        }

        return ret;
    }

    //******************************************************
    // return the node type
    virtual string NodeType() { return "varref"; }

    //******************************************************
    // define the visit method for this node
    virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
    const int SYMBOL = 0;
    const int EXPR = 1;
    int m_size = 0;
    int m_offset = 0;
    vector<int> m_rowsizes;
    vector<int> m_startindexes;

    //******************************************************
    string ElementsToString(const vector<int> & vec)
    {
        string ret = "\"";

        ret += to_string(vec[0]);

        for (unsigned int ii = 1; ii < vec.size(); ++ii)
        {
            ret += " ";
            ret += to_string(vec[ii]);
        }

        ret += "\"";

        return ret;
    }
};

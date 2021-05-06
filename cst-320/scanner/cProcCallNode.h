//**********************************************************
// file name: cProcCallNode.h
// purpose: defines an ast node for procedure calls.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cStmtNode.h"

class cProcCallNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cProcCallNode(cSymbol * name, cExprListNode * args = nullptr) : cStmtNode() 
        {
            if (name != nullptr)
            {
                AddChild(name);
            }

            if (args != nullptr)
            {
                AddChild(args);
            }
        }

        //**************************************************
        int GetParamSize()
        {
            int size = 0;
            cExprListNode * params = dynamic_cast<cExprListNode *>(GetChild(PARAM));

            for (int ii = 0; ii < params->GetNumParams(); ++ii)
            {
                size += params->GetParam(ii)->GetType()->GetSize();
            }

            return size;
        }

        //**************************************************
        virtual string AttributesToString()
        {
            return " paramSize =\"" + to_string(GetParamSize()) + "\"";
        }

        //**************************************************
        // return the name of the node type
        virtual string NodeType() { return "procCall"; }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
        const int NAME = 0;
        const int PARAM = 1;
};

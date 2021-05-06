//**********************************************************
// file name: cExprNode.h
// purpose: defines base class for all expressions.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cStmtNode.h"
#include "cDeclNode.h"
#include "cSymbolTable.h"

class cExprNode : public cStmtNode
{
    public:
        //**************************************************
        // constructor
        cExprNode() : cStmtNode() {}

        //**************************************************
        // used to determine the type of every expression
        virtual cDeclNode *GetType() = 0;

        virtual bool IsCharCompatible() { return false; }
};

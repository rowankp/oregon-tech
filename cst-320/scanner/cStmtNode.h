//**********************************************************
// filename: cStmtNode.h
// purpose: defines abstract class for a single statment.
//          NOTE: all statement types must inherit from 
//          this class.
// author: Rowan Parker
// date: 02/02/2020

#pragma once
#include "cAstNode.h"

class cStmtNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cStmtNode() : cAstNode() {}
};

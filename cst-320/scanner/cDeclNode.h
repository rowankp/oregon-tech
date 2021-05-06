//**********************************************************
// filename: cDeclNode.h
// purpose: defines base class for all declarations.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/03/2020

#pragma once
#include "cAstNode.h"
#include <string>
using std::string;

class cDeclNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cDeclNode() : cAstNode() {}
        
        //**************************************************
        // add child
        void AddDecl(cDeclNode * decl)
        {
            AddChild(decl);
        }

        //**************************************************
        // m_size acccesor
        int GetSize() { return m_size; }

        //**************************************************
        // m_offset accessor
        int GetOffset() { return m_offset; }

        //**************************************************
        // m_size mutator
        void SetSize(int size) { m_size = size; }

        //**************************************************
        // m_offset mutator
        void SetOffset(int offset) { m_offset = offset; }       

        virtual int NumRowSizes() { return 0; }
        virtual int NumStartIndexes() { return 0; }
        virtual int GetRowSize(int) { return 0; }
        virtual int GetStartIndex(int) { return 0;}

        virtual bool IsReal()  { return false; }
        virtual bool IsInt()   { return false; }
        virtual bool IsChar()  { return false; }
        virtual bool IsType()  { return false; }
        virtual bool IsFunc()  { return false; }
        virtual bool IsProc()  { return false; }
        virtual bool IsArray() { return false; }
        virtual string GetName() = 0;
        virtual cDeclNode * GetType() = 0;

    protected:
        int m_size = 0;
        int m_offset = 0;
};

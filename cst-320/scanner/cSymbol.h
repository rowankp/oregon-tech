//*********************************************************
// filename: cSymbol.h
// purpose: cSymbol class declaration. cSymbols are 
//          objects that represent identifiers and other 
//          such strings in the compiler.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 01/28/20
#pragma once
#include "cAstNode.h"
#include "pascalparse.h"
#include "cDeclNode.h"
#include <string>
#include <utility>

using std::string;

class cSymbol : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cSymbol(string name, int id = -1, bool isType = false) : cAstNode()
        {
            m_name = name;
            m_isType = isType;

            if (id == -1)
            {
                m_id = ++nextId;
                m_tokenType = IDENTIFIER;
            }
            else
            {
                m_id = id;
                m_tokenType = id;
            }
        }

        //**************************************************
        // returns a string with the attributes of the node
        string AttributesToString()
        {
            string result = " id =\"" +  std::to_string(m_id);
            result += "\" name=\"" + m_name + "\"";

            return result;
        }

        //**************************************************
        // m_name accessor
        string GetName() { return m_name; }

        //**************************************************
        // m_tokenType accessor 
        long long GetTokenType() { return m_tokenType; }

        //**************************************************
        // m_type mutator
        void SetTokenType(long long type) { m_tokenType = type; }

        //**************************************************
        // m_isType accessor
        bool IsType() { return m_isType; }

        //**************************************************
        // m_isType mutator
        void SetIsType(bool isType) { m_isType = isType; }

        //**************************************************
        // m_decl accessor
        cDeclNode * GetDecl() { return m_decl; }

        //**************************************************
        // m_decl mutator
        void SetDecl(cDeclNode * decl) { m_decl = decl; }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("sym"); }
 
        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    protected:
        static long long nextId;    
        long long m_id;            
        long long m_tokenType;
        string m_name;
        bool m_isType;
        cDeclNode * m_decl;
};

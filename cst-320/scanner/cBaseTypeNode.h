//**********************************************************
// filename: cBaseTypeNode.h
// purpose: defines an AST node for base types.
// author: Rowan Parker
// date: 02/02/2020

#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"

class cBaseTypeNode : public cDeclNode 
{
    public:
        //**************************************************
        // constructor
        cBaseTypeNode(string name, int size, bool isFloat) : cDeclNode()
        {
            m_name = name;
            m_size = size;
            m_isFloat = isFloat;
        }

        //**************************************************
        // constructor
        cBaseTypeNode(cSymbol * symbol) : cDeclNode()
        {
            if (symbol != nullptr)
            {
                m_name = symbol->GetName();

                if (m_name.compare("char") == 0)
                {
                    m_size = 1;
                    m_isFloat = false;
                }
                else if (m_name.compare("integer") == 0)
                {
                    m_size = 4;
                    m_isFloat = false;
                }
                else
                {
                    m_size = 8;
                    m_isFloat = true;
                }
            }
        }
        
        //**************************************************
        virtual string GetName()
        {
            return m_name;
        }

        //**************************************************
        virtual cDeclNode * GetType()
        {
            return this;
        }

        //**************************************************
        // is real?
        virtual bool IsReal()
        {
            if (m_size == 8)
            {
                return true;
            }

            return false;
        }

        //**************************************************
        // if int?
        virtual bool IsInt()
        {
            if (m_size == 4)
            {
                return true;
            }

            return false;
        }

        //**************************************************
        // is char?
        virtual bool IsChar()
        {
            if (m_size == 1)
            {
                return true;
            }

            return false;
        } 

        //**************************************************
        // returns a string with the attributes of the node
        virtual string AttributesToString() 
        {
            return " name=\"" + m_name + "\" size=\"" 
                   + std::to_string(m_size) + "\" isFloat=\"" 
                   + std::to_string(m_isFloat) + "\"";
        }

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("type"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    protected:
        string m_name;
        bool m_isFloat;
};

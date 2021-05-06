//**********************************************************
// filename: cVarDeclsNode.h
// purpose: defines a class to represent a list of var
//          declarations.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/01/2020

#pragma once
#include "cDeclsNode.h"
#include "cVarDeclNode.h"
#include "cBaseTypeNode.h"
#include <vector>

class cVarDeclsNode : public cDeclsNode
{
    public:
        //**************************************************
        // constructor
        cVarDeclsNode(cVarDeclNode * var = nullptr) : cDeclsNode()
        {
            if (var != nullptr)
            {
                AddChild(var);
            }
        }

        //**************************************************
        // constructor
        cVarDeclsNode(cIdListNode * list, cDeclNode * type) : cDeclsNode()
        {
            if (list != nullptr && type != nullptr)
            {
                for (int id = 0; id < list->GetNumId(); ++id)
                {
                    AddChild(new cVarDeclNode(type, list->GetId(id)));
                }
            }                
        }

        //**************************************************
        // add all children
        void AddVarDecls(cVarDeclsNode * vars) { AddAllChildren(vars); } 

        //**************************************************
        // add a child
        void AddVarDecl(cVarDeclNode * var) 
        {
            if (var != nullptr)
            { 
                AddChild(var); 
            }
        }

        //**************************************************
        cVarDeclNode * GetVarDecl(int child)
        {
            return dynamic_cast<cVarDeclNode *>(GetChild(child));
        }

        //**************************************************
        void SetSize(int size) { m_size = size; }

        //**************************************************
        virtual string AttributesToString()
        {
            return " size=\"" + to_string(m_size) + "\"";
        }

        //**************************************************
        // return a string with the node type
        virtual string NodeType() { return string("var_decls"); }
        
        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
        int m_size = 0;
};

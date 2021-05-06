//**********************************************************
// filename: cDeclsNode.h
// purpose: defines a class to represent a list of 
//          declarations.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/02/2020

#pragma once
#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        //**************************************************
        // constructor
        cDeclsNode(cDeclNode *decl = nullptr) : cAstNode()
        {
            if (decl != nullptr) AddChild(decl);
        }

        //**************************************************
        // copy all the decls from another node into this
        // one
        void AddDecls(cDeclsNode *decls) 
        { 
            if (decls != nullptr) AddAllChildren(decls); 
        }

        //**************************************************
        // add another decl to the list
        void AddDecl(cDeclNode *decl) 
        { 
            if (decl != nullptr) AddChild(decl); 
        }

	//***************************************************
        int GetNumDecls()
        {
            return NumChildren();
        }
		
	//***************************************************
	cDeclNode * GetDecl(int child)
	{
	    return dynamic_cast<cDeclNode *>(GetChild(child));
	}

        //**************************************************
        // returns a string with the node type
        virtual string NodeType() { return string("decls"); }

        //**************************************************
        // defines the visit method for this node
        virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }
};

//**********************************************************
// filename: cArrayDeclNode
// purpose: defines an ast node for array declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/09/2020

#pragma once
#include "cDeclNode.h"
#include "cSymbol.h"
#include "cSymbolTable.h"
#include "cDeclsNode.h"
#include "cRangeDeclNode.h"
#include <string>
using std::to_string;
#include <vector>
using std::vector;

class cArrayDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cArrayDeclNode(cSymbol * name, cDeclNode * type,  cDeclsNode * decls) : cDeclNode() 
        {
            if (name != nullptr && decls != nullptr && type != nullptr)
            {  
                if(symbolTable.GlobalLookup(name->GetName()) == name)
                {
                   name = new cSymbol(name->GetName());
                }

                symbolTable.Insert(name);
                name->SetDecl(this);
                name->SetIsType(true);

                AddChild(name);
                AddChild(type);
                AddChild(decls);    
            }
        }

       //***************************************************
       virtual cDeclNode * GetType() 
       {
           return dynamic_cast<cDeclNode *>(GetChild(TYPE));
       }

       //***************************************************
       void AddRowSize(int size) { m_rowsizes.push_back(size); }

       //***************************************************
       void AddStartIndex(int start) { m_startindexes.push_back(start); }

       //***************************************************
       void AddEndIndex(int end) { m_endindexes.push_back(end); }

       //***************************************************
       int GetRowSize(int index) { return m_rowsizes[index]; }

       //***************************************************
       int GetStartIndex(int index) { return m_startindexes[index]; }

       //***************************************************
       int GetEndIndex(int index) { return m_endindexes[index]; }

       //***************************************************
       int NumRowSizes() { return m_rowsizes.size(); }

       //***************************************************
       int NumStartIndexes() { return m_startindexes.size(); }

       //***************************************************
       // don't need a getter for number of end indexes 
       // because there should be a 1:1 relationship
       // between num start and num end
       int NumIndexes() { return m_startindexes.size(); }
       
       //***************************************************
       int NumRanges()
       {
            return dynamic_cast<cDeclsNode *>(GetChild(DECLS))->GetNumDecls();
       }
	   	   
       //***************************************************
       cRangeDeclNode * GetRange(int index)
       {
           cDeclsNode * decls = dynamic_cast<cDeclsNode *>(GetChild(DECLS));
           return dynamic_cast<cRangeDeclNode *>(decls->GetDecl(index));
       }
       
       //***************************************************
       virtual string GetName() 
       { 
           return dynamic_cast<cSymbol *>(GetChild(NAME))->GetName(); 
       }

       //***************************************************
       virtual string AttributesToString()
       {
            return " size=\"" + to_string(m_size) +
                   "\" rowsizes=" + ElementsToString(m_rowsizes) +
                   " startindexes=" + ElementsToString(m_startindexes);            
       }

       //***************************************************      
       virtual bool IsType() { return true; }

       //***************************************************
       virtual bool IsArray() { return true; }

       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "array"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    private:
       const int NAME = 0;
       const int TYPE = 1;
       const int DECLS = 2;
       vector<int> m_rowsizes;
       vector<int> m_startindexes;
       vector<int> m_endindexes;

       //***************************************************
       // formats the elements of the vectors for printing
       string ElementsToString(const vector<int> vec)
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

//**********************************************************
// filename: cFuncDeclNode
// purpose: defines an ast node for function  declarations.
// author: Rowan Parker (rowan.prker@oit.edu)
// date: 02/07/2020

#pragma once
#include "cSymbolTable.h"
#include "cDeclNode.h"
#include "cVarDeclsNode.h"
#include "cBlockNode.h"
#include "cSymbol.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        //**************************************************
        // constructor
        cFuncDeclNode(cSymbol * symbol) : cDeclNode() 
        {
            
            AddChild(nullptr);
            AddChild(nullptr);
            AddChild(nullptr);
            AddChild(nullptr);
   
            if (symbol != nullptr)
            {
                std::string name = symbol->GetName();

                // search for symbol globally
                if (symbolTable.GlobalLookup(name) != nullptr)
                {
                    // search for symbol locally
                    if (symbolTable.LocalLookup(name) != nullptr)
                    {
                        // check is correct cast and for forward declartion
                        if (!(symbol->GetDecl()->IsFunc()))
                        {
                            SemanticParseError("Symbol " + name 
                                               + " already exists in current scope ");
                        }
                        else
                        {
                            // copy the children of the forward declaration
                            cFuncDeclNode * func = dynamic_cast<cFuncDeclNode *>(symbol->GetDecl());
                            SetChild(NAME, func->GetChild(NAME));
                            SetChild(RETURN, func->GetChild(RETURN));
                            SetChild(PARAM, func->GetChild(PARAM));
                            SetChild(BLOCK, func->GetChild(BLOCK));
                        }
                    }
                    else
                    {
                        symbol = new cSymbol(name);
                        symbol->SetDecl(this);
                    }
                }
                else
                {
                    symbol->SetDecl(this);
                    symbolTable.Insert(symbol);
                }    

                
                // check if child already exists
                if (GetChild(NAME) == nullptr)
                {
                    SetChild(NAME, symbol);
                }
            }
        }

       //***************************************************
       // adds a decls node as a child
       void AddParamSpec(cVarDeclsNode * param)
       {
           if (GetParamSpec() == nullptr)
           {
                SetChild(PARAM, param);
           }
           else
           {
               if (GetParamSpec()->GetNumDecls() != param->GetNumDecls())
               {
                   SemanticParseError(GetName() + " redeclared with " + 
                                      "different number of parameters");
               }
               else
               {
                   SetChild(PARAM, param);
               }
           }
       }

       //***************************************************
       // adds a type decl as a child
       void AddType(cDeclNode * type)
       {
          if (type == nullptr)
          {
              SemanticParseError(GetName() + " declared without return type ");
          }
          else
          {
             cDeclNode * declared = GetType();

             // check if child already exists 
             if (declared == nullptr)
             {
                SetChild(RETURN, type);
             }
             else
             {
                // type compare
                if (declared != type)
                {
                    SemanticParseError(GetName() + " previsously declared " + 
                                       "with different return type ");
                }
                else
                {
                    SetChild(RETURN, type);
                }
             }  
          }
       }

       //***************************************************
       // adds a block decl as a child
       void AddBlock(cBlockNode * block)
       {
           cSymbol * symbol = dynamic_cast<cSymbol *>(GetChild(NAME));
           cFuncDeclNode * func = dynamic_cast<cFuncDeclNode *>(symbol->GetDecl());

           if (symbol->GetDecl()->IsFunc())
           {
                if (func->GetChild(BLOCK) == nullptr)
                {
                     symbol->SetDecl(this);
                    SetChild(BLOCK, block);
                }
                else
                {
                    SemanticParseError(GetName() + " already has a definition");
                }
           }
       }
      
       //***************************************************
       // get block child
       cBlockNode * GetBlock()
       {
           return dynamic_cast<cBlockNode *>(GetChild(BLOCK));
       }

       //***************************************************
       // get type
       cDeclNode * GetType()
       {
           return dynamic_cast<cDeclNode *>(GetChild(RETURN));
       }

       //***************************************************
       // get param spec
       cVarDeclsNode * GetParamSpec()
       {
           return dynamic_cast<cVarDeclsNode *>(GetChild(PARAM));
       }

       //***************************************************
       // get num params
       int GetNumParams()
       {
           if (GetParamSpec() == nullptr)
           {
               return 0;
           }
        
           return GetParamSpec()->GetNumDecls();
       }

       //***************************************************
       virtual string AttributesToString()
       {
           return " size=\"" + to_string(m_size) +
                  "\" offset=\"" + to_string(m_offset) + "\"";
       }

       //***************************************************
       // get func name
       virtual string GetName()
       {
           return dynamic_cast<cSymbol *>(GetChild(NAME))->GetName();
       }

       //***************************************************
       // return is func
       virtual bool IsFunc() { return true; }

       //***************************************************
       // returns a string with the node type
       virtual string NodeType() { return "func"; } 

       //***************************************************
       // defines the visit method for this node
       virtual void Visit(cVisitor * visitor) { visitor->Visit(this); }

    protected:
       const int NAME = 0;
       const int RETURN = 1;
       const int PARAM = 2;
       const int BLOCK = 3;
};

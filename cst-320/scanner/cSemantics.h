//**********************************************************
// file: cSemantics.h
// purpose: subclass of cVisitor for semantic parsing
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/23/2020

#include "astnodes.h"
#include "cVisitor.h"
#include "cAstNode.h"
#include <string>
using std::string;

class cSemantics : public cVisitor
{
    public:
        //**************************************************
        cSemantics() : cVisitor()
        { }

        //**************************************************
        virtual void VisitAllNodes(cAstNode * node)
        {
            node->VisitAllChildren(this);
        }

        //**************************************************
        virtual void Visit(cFuncExprNode * func) 
        {
            func->VisitAllChildren(this);
            
            // func name
            string funcName = func->GetFunc()->GetName();
            
            // func decl
            cFuncDeclNode * funcDecl = dynamic_cast<cFuncDeclNode *>(func->GetFunc()->GetDecl());

            if (func->GetFunc()->GetDecl() == nullptr)
            {
                func->SemanticError(funcName + " is not declared");
            }
            else if (func->GetFunc()->GetDecl()->IsFunc() == false)
            {
                func->SemanticError(funcName + " is not a function");
            }
            else if (funcDecl->GetBlock() == nullptr)
            {
                func->SemanticError(funcName + " is not fully defined");
            }
            else if (func->GetExpr() != nullptr)
            {
                if (func->GetExpr()->GetNumParams() != funcDecl->GetNumParams())
                {
                    func->SemanticError(funcName + " called with wrong number of arguments");
                }
            }
            else if (func->GetExpr() == nullptr)
            {
                if (funcDecl->GetNumParams() != 0)
                {
                    func->SemanticError(funcName + " called with wrong number of arguments");
                }
            }    
        }

        //**************************************************
        virtual void Visit(cVarExprNode * var)
        {
            var->VisitAllChildren(this);
            
            if (var->GetSymbol()->GetDecl()  == nullptr)
            {
                var->SemanticError("Variable " + var->GetSymbol()->GetName() +
                                   " is not defined");
            }
        }

        //**************************************************
        virtual void Visit(cAssignNode * stmt)
        {
            stmt->VisitAllChildren(this);

            cDeclNode * lval = stmt->GetLVal()->GetType();
            cDeclNode * rval = stmt->GetRVal()->GetType();

            if (lval != nullptr && rval != nullptr)
            {
                if (lval != rval)
                {
                    string lvalName = lval->GetName();
                    string rvalName = rval->GetName();
                
                    if (lval->IsType())
                    {   

                    }
                    else
                    {   
                        // test real assigned to invalid type
                        if ((lval->IsInt() && rval->IsReal()) || (lval->IsChar() && rval->IsReal()))
                        {
                            stmt->SemanticError("Cannot assign " + rvalName + 
                                                " to " + lvalName);
                        }  
                        // test for char = int
                        else if (lval->IsChar() && rval->IsInt() && 
                                 stmt->GetRVal()->IsCharCompatible() == false)
                        {
                            stmt->SemanticError("Cannot assign " + rvalName + 
                                                " to " + lvalName);
                        }
                
                    }
                }   
            }
        }
};

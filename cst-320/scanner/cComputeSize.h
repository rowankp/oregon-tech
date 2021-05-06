//**********************************************************
// file: cComputeSize.h
// purpose: subclass of cVisitor for size allocation
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 03/04/2020

#include "astnodes.h"
#include "cVisitor.h"
#include "cAstNode.h"
#include <string>
using std::string;

class cComputeSize : public cVisitor
{
    public:
        //**************************************************
        cComputeSize() : cVisitor()
        { }

        //**************************************************
        virtual void VisitAllNodes(cAstNode * node)
        {
            node->VisitAllChildren(this);
        }

        //**************************************************
        virtual void Visit(cBlockNode * block)
        {
            int saved = m_offset;
            
            block->VisitAllChildren(this);
            WordAlign();
            block->SetSize(m_offset);

            m_offset = saved;
        }

        //**************************************************
        virtual void Visit(cVarDeclsNode * decl)
        {         
            int saved = m_offset;

            // adjust for RA and FP
            // recall:
            //    a3
            //    a2
            //    a1
            //    a0
            // ----------- end previous frame
            //    RA
            //    FP
            // ------------ sp
            // must shift 3 positions upward to grab args 
            // -3 * 4 = 12
            m_offset = -12;

            // set offset direction for param spec
            m_offsetDirection = -1;

            decl->VisitAllChildren(this);

            WordAlign(); 

            decl->SetSize(-12 - m_offset);

            // reset offset direction 
            m_offsetDirection = 1;

            // restore offset
            m_offset = saved;
        }

        //**************************************************
        virtual void Visit(cVarDeclNode * decl)
        {
            decl->SetSize(decl->GetType()->GetSize());
            
            if (m_offsetDirection == -1 || decl->GetSize() >= WORD_SIZE)
            {
                WordAlign();
            }

            decl->SetOffset(m_offset);
            
            m_offset += decl->GetSize() * m_offsetDirection;
        }

        //**************************************************
        virtual void Visit(cVarExprNode * varref)
        {
             varref->VisitAllChildren(this);
            
             cDeclNode * decl = varref->GetSymbol()->GetDecl()->GetType();

             // check if array
             if (decl->IsArray())
             {
                for (int ii = 0; ii < decl->NumRowSizes(); ++ii)
                {
                    varref->AddRowSize(decl->GetRowSize(ii));
                    varref->AddStartIndex(decl->GetStartIndex(ii));  
                }
             }

             varref->SetSize(varref->GetType()->GetSize());
             varref->SetOffset(varref->GetSymbol()->GetDecl()->GetOffset());
        }

        //**************************************************
        virtual void Visit(cArrayDeclNode * arr)
        {
            // get size of type
            int totalSize = arr->GetType()->GetSize();
            
            // push type size for first dimension
            arr->AddRowSize(totalSize);
            // push start index for first dimension
            arr->AddStartIndex(arr->GetRange(0)->GetStart());
            // push end index for first dimension
            arr->AddEndIndex(arr->GetRange(0)->GetEnd());
            
            // calculate length for first dimension
            int length = arr->GetEndIndex(0) - arr->GetStartIndex(0) + 1;

            // push start and end indexes and rowsizes for other dimensions
            for (int ii = 1; ii < arr->NumRanges(); ++ii)
	    {
                arr->AddStartIndex(arr->GetRange(ii)->GetStart());
                arr->AddEndIndex(arr->GetRange(ii)->GetEnd());

                int rowSize = length * arr->GetRowSize(ii - 1);

                arr->AddRowSize(rowSize);
                totalSize *= length;                
                
                length = arr->GetEndIndex(ii) - arr->GetStartIndex(ii) + 1;
	    }

            // calculate size 
            totalSize *= length;

            arr->SetSize(totalSize);
        }

        //**************************************************
        virtual void Visit(cFuncDeclNode * func)
        {
            int saved = m_offset;
            
            m_offset = 0;

            func->SetSize(func->GetType()->GetSize());
            func->SetOffset(m_offset);

            m_offset += func->GetSize();
            WordAlign();
            func->GetParamSpec()->Visit(this);
            func->GetBlock()->Visit(this);

            m_offset = saved;
        }

        //**************************************************
        virtual void Visit(cFuncExprNode * func)
        { 
            func->VisitAllChildren(this);

            int totalSize = 0;
            
            for (int ii = 0; ii < func->GetNumParams(); ++ii)
            {
                int paramSize = func->GetParam(ii)->GetType()->GetSize();

                if (paramSize < WORD_SIZE)
                {
                    paramSize -= paramSize % WORD_SIZE;
                    paramSize += WORD_SIZE;
                }

                totalSize += paramSize;
            }            

            func->SetSize(totalSize);
        }

        //**************************************************
        virtual void Visit(cProcDeclNode * proc)
        {
            int saved = m_offset;
            m_offset = 0;

            proc->VisitAllChildren(this);

            m_offset = saved;
        }

    private:
        //**************************************************
        void WordAlign()
        {
            if (m_offset % WORD_SIZE != 0)
            {
                m_offset -= (m_offset % WORD_SIZE) * m_offsetDirection;
                m_offset += WORD_SIZE * m_offsetDirection;
            }
        }

        int m_offset = 0;
        int m_offsetDirection = 1;
        const int WORD_SIZE = 4;
};

%{
//**********************************************************
// filename: pascal.y
// purpose: parser definition file. bison uses this file to 
//          generate the parser.
// author: Rowan Parker (rowan.parker@oit.edu)
// date: 02/02/2020

#include <iostream>
#include "lex.h"
#include "astnodes.h"

#define CHECK_ERROR() { if (g_semanticErrorHappened) \
                      { g_semanticErrorHappened = false; } }

#define PROP_ERROR()  { if (g_semanticErrorHappened) \
                      { g_semanticErrorHappened = false; \
                        YYERROR; } }           
%}

%locations

 /* union defines the type for lexical values */
%union{
    int                 int_val;
    double              real_val;
    cAstNode*           ast_node;
    cBlockNode*         block_node;
    cBaseTypeNode*      base_type;
    cDeclNode*          decl_node;
    cDeclsNode*         decls_node;
    cExprListNode*      expr_list;
    cExprNode*          expr_node;
    cFuncDeclNode*      func_decl;
    cIdListNode*        id_list;
    cProcDeclNode*      proc_decl;
    cProgramNode*       program_node;
    cStmtNode*          stmt_node;
    cStmtsNode*         stmts_node;
    cSymbol*            symbol;
    cVarDeclNode*       var_decl;
    cVarDeclsNode*      var_decls;
    cVarExprNode*       var_expr;
    }

%{
    int yyerror(const char *msg);
    static bool g_semanticErrorHappened;
    cAstNode *yyast_root;
%}

%start  program

%token PROGRAM PROCEDURE FUNCTION FORWARD
%token OPEN CLOSE
%token WRITE
%token WHILE IF THEN ELSE REPEAT UNTIL
%token FOR DO TO DOWNTO
%token CONST TYPE VAR
%token RECORD ARRAY OF
%token NIL
%token CHAR INTEGER REAL
%token JUNK_TOKEN

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   CHAR_VAL
%token <int_val>   INT_VAL
%token <real_val>  REAL_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   NOT
%token <int_val>   DIV
%token <int_val>   MOD
%token <int_val>   NOT_EQUAL
%token <int_val>   LE
%token <int_val>   GE
%token <int_val>   ASSIGN

%type <program_node>    program
%type <symbol>          header
%type <block_node>      block
%type <decl_node>       type
%type <decls_node>      decls
%type <decls_node>      constdecls
%type <decls_node>      constdecl
%type <expr_node>       constant
%type <decls_node>      typedecls
%type <decls_node>      typedecl
%type <decl_node>       singleType
%type <decls_node>      rangeList
%type <decl_node>       range
%type <var_decls>       goodvar
%type <var_decls>       onevar
%type <var_decls>       recorddef
%type <var_decls>       vardecls
%type <var_decls>       vardecl;
%type <decls_node>      procdecls
%type <var_decls>       paramSpec
%type <decl_node>       procdecl
%type <var_decls>       parlist
%type <id_list>         idlist
%type <expr_node>       func_call
%type <func_decl>       funcProto
%type <func_decl>       funcHeader
%type <proc_decl>       procHeader
%type <stmts_node>      statements
%type <stmt_node>       statement
%type <expr_node>       expr
%type <expr_node>       oneExpr
%type <expr_node>       addit
%type <expr_node>       term
%type <expr_node>       fact
%type <var_expr>        variable
%type <symbol>          varpart
%type <expr_list>       exprList
%type <ast_node>        recHeader

%%

program: header block '.'
                                { 
                                    $$ = new cProgramNode($1, $2);
                                    CHECK_ERROR();
                                    symbolTable.IncreaseScope();
                                    yyast_root = $$;
                                    if (yynerrs == 0) 
                                        YYACCEPT;
                                    else
                                        YYABORT;
                                }
header: PROGRAM IDENTIFIER ';'
                                { $$ = $2; }
block:  decls OPEN statements CLOSE
                                { 
                                    $$ = new cBlockNode($1, $3);
                                    CHECK_ERROR();
                                }
    
decls: constdecls typedecls vardecls procdecls
                                {
                                    if ($1 != nullptr || $2 != nullptr ||
                                        $3 != nullptr || $4 != nullptr)
                                    {
                                        $$ = new cDeclsNode();
                                        CHECK_ERROR();
                                    }
                                    else { $$ = nullptr; }
                                    
                                    if ($$ != nullptr)
                                    {
                                        $$->AddDecls($1);
                                        $$->AddDecls($2);
                                        $$->AddDecls($3);
                                        $$->AddDecls($4);
                                    }
                                }
constdecls: CONST constdecl ';'
                                { $$ = $2; }
        | /*empty */
                                { $$ = nullptr; }
constdecl: constdecl ';' IDENTIFIER '=' constant 
                                {
                                    $$ = $1;
                                    $$->AddDecl(new cConstDeclNode($3, $5));
                                    CHECK_ERROR();
                                }
        |  IDENTIFIER '=' constant 
                                { 
                                    $$ = new cDeclsNode();
                                    CHECK_ERROR(); 
                                    $$->AddDecl(new cConstDeclNode($1, $3)); 
                                }
typedecls: TYPE typedecl
                                { $$ = $2; }
        | /*empty */
                                { $$ = nullptr; }
typedecl: typedecl singleType
                                {
                                    $$ = $1;
                                    $$->AddDecl($2); 
                                }
        |  singleType
                                { 
                                    $$ = new cDeclsNode();
                                    CHECK_ERROR();
                                    $$->AddDecl($1); 
                                }
        |  error ';'
                                { $$ = nullptr; }
singleType:  IDENTIFIER '=' recHeader recorddef ';'
                                { 
                                    $$ = new cRecordDeclNode($1, $4); 
                                    CHECK_ERROR();
                                }
        | IDENTIFIER '=' ARRAY '[' rangeList ']' OF type ';'
                                { 
                                    $$ = new cArrayDeclNode($1, $8, $5); 
                                    CHECK_ERROR();
                                }
rangeList: rangeList ',' range
                                {
                                    $$ = $1;
                                    $$->AddDecl($3); 
                                }
        |  range
                                { 
                                    $$ = new cDeclsNode();
                                    CHECK_ERROR();
                                    $$->AddDecl($1);
                                }
range: INT_VAL '.' '.' INT_VAL
                                { 
                                    $$ = new cRangeDeclNode($1, $4); 
                                    CHECK_ERROR();
                                }

vardecls: VAR vardecl
                                { $$ = $2; }
        | /* empty */
                                { $$ = nullptr; }
vardecl: vardecl onevar
                                {
                                    $$ = $1;
                                    $$->AddVarDecls($2);
                                }
        | onevar
                                { $$ = $1; }
onevar: goodvar ';'
                                { $$ = $1; }
        | error ';'
                                { $$ = nullptr; }
goodvar: idlist ':' type
                                { 
                                    $$ = new cVarDeclsNode($1, $3); 
                                    CHECK_ERROR();
                                }
procdecls: procdecls procdecl
                                { 
                                    if ($1 != nullptr) 
                                    {
                                        $$ = $1;
                                    }
                                    else
                                    { 
                                        $$ = new cDeclsNode();
                                        CHECK_ERROR();
                                    }
                                    
                                    $$->AddDecl($2); 
                                }
        | /* empty */
                                { $$ = nullptr; }

procdecl: procHeader paramSpec ';' block ';'
                                { 
                                    $1->AddParamSpec($2);
                                    $1->AddBlock($4);
                                    $$ = $1;
                                    symbolTable.DecreaseScope(); 
                                }
        |  procHeader paramSpec ';' FORWARD ';'
                                { 
                                    $1->AddParamSpec($2);
                                    $$ = $1;
                                    symbolTable.DecreaseScope();
                                }
        |  funcProto ';' block ';'
                                {
                                    $1->AddBlock($3);
                                    $$ = $1;
                                    symbolTable.DecreaseScope();
                                }
        |  funcProto ';' FORWARD ';'
                                { 
                                    $1->AddBlock(nullptr);
                                    $$ = $1; 
                                    symbolTable.DecreaseScope();
                                }
        |  error ';' block ';'
                                { $$ = nullptr; }
        |  error ';' FORWARD ';'
                                { $$ = nullptr; }
procHeader: PROCEDURE IDENTIFIER 
                                 {
                                    $$ = new cProcDeclNode($2);
                                    CHECK_ERROR();
                                    symbolTable.IncreaseScope();
                                 }
funcHeader: FUNCTION IDENTIFIER
                                {
                                    $$ = new cFuncDeclNode($2);
                                    CHECK_ERROR();
                                    symbolTable.IncreaseScope();
                                }
funcProto: funcHeader paramSpec ':' type
                                { 
                                    $$ = $1;
                                    $$->AddType($4);
                                    $$->AddParamSpec($2);
                                }   
paramSpec: '(' parlist ')'
                                { $$ = $2; }
        | /* empty */
                                { $$ = nullptr; }

idlist: idlist ',' IDENTIFIER
                                {
                                    $$ = $1;
                                    $$->AddId($3);
                                }
    |    IDENTIFIER
                                { 
                                    $$ = new cIdListNode($1); 
                                    CHECK_ERROR();
                                }

parlist: parlist ';' VAR idlist ':' type 
                                { 
                                    $$ = $1;
                                    $$->AddDecls(new cVarDeclsNode($4, $6));
                                    CHECK_ERROR();
                                }
    |    parlist ';' idlist ':' type 
                                { 
                                    $$ = $1;
                                    $$->AddDecls(new cVarDeclsNode($3, $5));
                                    CHECK_ERROR();
                                }
    |    VAR idlist ':' type
                                { 
                                    $$ = new cVarDeclsNode($2, $4); 
                                    CHECK_ERROR();
                                }
    |    idlist ':' type
                                { 
                                    $$ = new cVarDeclsNode($1, $3);
                                    CHECK_ERROR();
                                }

type: TYPE_ID
                                { 
                                    if ($1->GetDecl() != nullptr)
                                    {
                                        $$ = $1->GetDecl();
                                    }
                                    else
                                    {
                                        $$ = yylval.symbol->GetDecl();
                                    }
                                 }
recHeader: RECORD
                                { 
                                    $$ = nullptr;
                                    symbolTable.IncreaseScope();
                                }
recorddef: vardecl CLOSE
                                {
                                    $$ = $1;
                                    symbolTable.DecreaseScope();
                                }
constant: INT_VAL
                                { 
                                    $$ = new cIntExprNode($1);
                                    CHECK_ERROR();
                                }
    |   '-' INT_VAL
                                { 
                                    $$ = new cUnaryExprNode(new cOpNode('-'), new cIntExprNode($2)); 
                                    CHECK_ERROR();
                                }

statements: statements statement
                                { 
                                     $$ = $1;
                                     $$->AddNode($2);
                                }
    |   statement
                                { 
                                    $$ = new cStmtsNode($1); 
                                    CHECK_ERROR();
                                }

statement: variable ASSIGN expr ';'
                                { 
                                    $$ = new cAssignNode($1, $3); 
                                    CHECK_ERROR();
                                }
    |   IF expr THEN statement
                                { 
                                    $$ = new cIfNode($2, $4); 
                                    CHECK_ERROR();
                                }
    |   IF expr THEN statement ELSE statement
                                { 
                                    $$ = new cIfNode($2, $4, $6);
                                    CHECK_ERROR();
                                }
    |   REPEAT statements UNTIL expr ';'
                                { }
    |   WHILE expr DO statement
                                { 
                                    $$ = new cWhileNode($2, $4); 
                                    CHECK_ERROR();
                                }
    |   FOR IDENTIFIER ASSIGN expr TO expr DO statement
                                {}
    |   FOR IDENTIFIER ASSIGN expr DOWNTO expr DO statement
                                {}
    |   IDENTIFIER '(' exprList ')' ';'
                                { 
                                    $$ = new cProcCallNode($1, $3); 
                                    CHECK_ERROR();
                                }
    |   IDENTIFIER ';'
                                { 
                                    $$ = new cProcCallNode($1); 
                                    CHECK_ERROR();
                                }
    |   WRITE '(' exprList ')' ';'
                                { 
                                    $$ = new cWriteNode($3); 
                                    CHECK_ERROR();
                                }
    |   OPEN statements CLOSE
                                { 
                                    $$ = new cCompoundStmtNode($2);     
                                    CHECK_ERROR();      
                                }
    |   NIL ';'
                                { 
                                    $$ = new cNilNode(); 
                                    CHECK_ERROR();
                                }
    |   error ';'
                                { $$ = nullptr; }

exprList: exprList ',' oneExpr
                                {
                                    $$ = $1;
                                    $$->AddNode($3); 
                                }
        | oneExpr
                                { 
                                    $$ = new cExprListNode($1); 
                                    CHECK_ERROR();
                                }
        | /* empty */
                                { $$ = nullptr; }
oneExpr: expr
                                { $$ = $1; }

func_call:  IDENTIFIER '(' exprList ')'
                                { 
                                    $$ = new cFuncExprNode($1, $3); 
                                    CHECK_ERROR();
                                }

variable: variable '.' varpart
                                {
                                    $$ = $1;
                                    $$->AddSymbol($3); 
                                }
        | variable '[' exprList ']'
                                {
                                    $$ = $1;
                                    $$->AddExprList($3);
                                }
        | varpart
                                { 
                                    $$ = new cVarExprNode($1); 
                                    CHECK_ERROR();
                                }

varpart:  IDENTIFIER
                                { $$ = $1; }

expr:       expr '=' addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('='), $3);
                                    CHECK_ERROR();
                                }
        |   expr '>' addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('>'), $3);
                                    CHECK_ERROR(); 
                                }
        |   expr '<' addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('<'), $3);
                                    CHECK_ERROR();
                                }
        |   expr LE addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(LE), $3); 
                                    CHECK_ERROR();
                                }
        |   expr GE addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(GE), $3); 
                                    CHECK_ERROR();
                                }
        |   expr NOT_EQUAL addit
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(NOT_EQUAL), $3); 
                                    CHECK_ERROR();
                                }
        |   addit
                                { $$ = $1; }

addit:      addit '+' term
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('+'), $3); 
                                    CHECK_ERROR();
                                }
        |   addit '-' term
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('-'), $3);
                                    CHECK_ERROR(); 
                                }
        |   addit OR term
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(OR), $3); 
                                    CHECK_ERROR();
                                }
        |   term
                                { $$ = $1; }
        |   '-' term
                                { 
                                    $$ = new cUnaryExprNode(new cOpNode('-'), $2); 
                                    CHECK_ERROR();
                                }

term:       term '*' fact
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('*'), $3);
                                    CHECK_ERROR();
                                }
        |   term '/' fact
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode('/'), $3); 
                                    CHECK_ERROR();
                                }
        |   term MOD fact
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(MOD), $3); 
                                    CHECK_ERROR();
                                }
        |   term DIV fact
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(DIV), $3); 
                                    CHECK_ERROR();
                                }
        |   term AND fact
                                { 
                                    $$ = new cBinaryExprNode($1, new cOpNode(AND), $3); 
                                    CHECK_ERROR();
                                }
        |   fact
                                { $$ = $1; }

fact:        '(' expr ')'
                                { $$ = $2; }
        |   INT_VAL
                                { 
                                    $$ = new cIntExprNode($1); 
                                    CHECK_ERROR();
                                }
        |   REAL_VAL
                                { 
                                    $$ = new cRealExprNode($1); 
                                    CHECK_ERROR();
                                }
        |   variable
                                { $$ = $1; }
        |   func_call
                                { $$ = $1; }
        |   NOT fact
                                { 
                                    $$ = new cUnaryExprNode(new cOpNode(NOT), $2); 
                                    CHECK_ERROR();
                                }

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cout << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}

// Function that gets called when a semantic error happens
void SemanticParseError(std::string error)
{
    std::cout << "ERROR: " << error << " on line " 
              << yylineno << "\n";
    g_semanticErrorHappened = true;
    yynerrs++;
}

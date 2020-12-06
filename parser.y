%{
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static AstNode *root;

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
    class AstNode;
}

    /* For yylval */
%union {
    /* basic semantic value */
    char *identifier; // ID
    char *var_type; // int float string
    std::vector<char*> ch_arr;

    AstNode *node;
    std::vector<AstNode*> *nodes;
};
%type <ch_arr>     IdList
CompoundStatement
%type <identifier> ProgramName ID 

    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token ASSIGN
%left OR
%left AND
%right NOT
%left LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left PLUS MINUS
%left MULTIPLY DIVIDE MOD
%right UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token INT_LITERAL
%token REAL_LITERAL
%token STRING_LITERAL

%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(@1.first_line, @1.first_column,
                               $1,$3,$4,$5);

        free($1);free($3);free($4);free($5);
    }
;

ProgramName:
    ID
;

DeclarationList:
    Epsilon{
        $$ = NULL;
    }
    |
    Declarations{
        $$ = $1;
    }
;

Declarations:
    Declaration{
        std::vector<AstNode*> *tmp_ptr;
        tmp_ptr->push_back($1);
        $$ = tmp_ptr;
    }
    |
    Declarations Declaration{
        $1->push_back($2);
        $$ = $1;
    }
;

FunctionList:
    Epsilon
    |
    Functions
;

Functions:
    Function
    |
    Functions Function
;

Function:
    FunctionDeclaration
    |
    FunctionDefinition
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon
    |
    FormalArgs
;

FormalArgs:
    FormalArg
    |
    FormalArgs SEMICOLON FormalArg
;

FormalArg:
    IdList COLON Type
;

IdList:
    ID{
        vector<char*> *v;
        v->push_back($1);
        $$ = $1;
    }
    |
    IdList COMMA ID{
        $1->push_back($3);
        $$ = $1;
    }
;

ReturnType:
    COLON ScalarType
    |
    Epsilon
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON{
        vector<VariableNode*> *tmp;
        for(int i=0;i<($2)->size();i++){
            tmp->push_back(new VariableNode(@1.first_line,@1.first_column,($2)->at(i),$4));
        }
        $$ = new DeclNode(@1.first_line,@1.first_column,tmp);
        ($$)->Constant_value=NULL;
        free($2);free($4);
    }
    |
    VAR IdList COLON LiteralConstant SEMICOLON{
        vector<VariableNode*> *tmp;
        for(int i=0;i<($2)->size();i++){
            tmp->push_back(new VariableNode(@1.first_line,@1.first_column,($2)->at(i),($4)->at(1),($4)->at(0)));
        }
        $$ = new DeclNode(@1.first_line,@1.first_column,tmp,($4)->at(1));
        ($$)->Constant_value = new ConstantValueNode(@1.first_line,@1.first_column,($4)->at(0));
        free($2);free($4);
    }
;

Type:
    ScalarType {$$ = $1;}
    |
    ArrType {$$ = $1;}
;

ScalarType:
    INTEGER {$$ = "integer";}
    |
    REAL    {$$ = "real";}
    |
    STRING  {$$ = "string";}
    |
    BOOLEAN {$$ = "boolean";}
;

ArrType:
    ArrDecl ScalarType {
        std::string tmp;
        tmp+=$2;
        tmp+=' ';
        for(int i=0;i<($1)->size();i++)
            tmp+='[',tmp+=($1)->at(i),tmp+=']';
        $$ = tmp.c_str();
    }
;

ArrDecl:
    ARRAY INT_LITERAL OF{
        vector<char*> *tmp;
        tmp->push_back(INT_LITERAL);
        $$ = tmp;
    }
    |
    ArrDecl ARRAY INT_LITERAL OF{
        $1->push_back($3);
        $$ = $1;
    }
;

LiteralConstant:
    NegOrNot INT_LITERAL{
        vector<char*> *tmp;
        std::string st_tmp;
        st_tmp+=$1;
        st_tmp+=$2;
        tmp->push_back(st_tmp.c_str());
        tmp->push_back("integer");
        $$ = tmp;
    }
    |
    NegOrNot REAL_LITERAL{
        vector<char*> *tmp;
        std::string st_tmp;
        st_tmp+=$1;
        st_tmp+=$2;
        tmp->push_back(st_tmp.c_str());
        tmp->push_back("real");
        $$ = tmp;   
    }
    |
    StringAndBoolean{
        $$ = $1;
    }
;

NegOrNot:
    Epsilon {$$ = $1;}
    |
    MINUS %prec UNARY_MINUS {$$ = "-";}
;

StringAndBoolean:
    STRING_LITERAL{
        vector<char*> *tmp;
        tmp->push_back($1);
        tmp->push_back("string");
        $$ = tmp;
    }
    |
    TRUE{
        vector<char*> *tmp;
        tmp->push_back($1);
        tmp->push_back("boolean");
        $$ = tmp;
    }
    |
    FALSE{
        vector<char*> *tmp;
        tmp->push_back($1);
        tmp->push_back("boolean");
        $$ = tmp;
    }
;

IntegerAndReal:
    INT_LITERAL
    |
    REAL_LITERAL
;

    /*
       Statements
                  */

Statement:
    CompoundStatement
    |
    Simple
    |
    Condition
    |
    While
    |
    For
    |
    Return
    |
    FunctionCall
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON
    |
    PRINT Expression SEMICOLON
    |
    READ VariableReference SEMICOLON
;

VariableReference:
    ID ArrRefList
;

ArrRefList:
    Epsilon
    |
    ArrRefs
;

ArrRefs:
    L_BRACKET Expression R_BRACKET
    |
    ArrRefs L_BRACKET Expression R_BRACKET
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF
;

ElseOrNot:
    ELSE
    CompoundStatement
    |
    Epsilon
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO
;

Return:
    RETURN Expression SEMICOLON
;

FunctionCall:
    FunctionInvocation SEMICOLON
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS
;

ExpressionList:
    Epsilon
    |
    Expressions
;

Expressions:
    Expression
    |
    Expressions COMMA Expression
;

StatementList:
    Epsilon
    |
    Statements
;

Statements:
    Statement
    |
    Statements Statement
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS
    |
    MINUS Expression %prec UNARY_MINUS
    |
    Expression MULTIPLY Expression
    |
    Expression DIVIDE Expression
    |
    Expression MOD Expression
    |
    Expression PLUS Expression
    |
    Expression MINUS Expression
    |
    Expression LESS Expression
    |
    Expression LESS_OR_EQUAL Expression
    |
    Expression GREATER Expression
    |
    Expression GREATER_OR_EQUAL Expression
    |
    Expression EQUAL Expression
    |
    Expression NOT_EQUAL Expression
    |
    NOT Expression
    |
    Expression AND Expression
    |
    Expression OR Expression
    |
    IntegerAndReal
    |
    StringAndBoolean
    |
    VariableReference
    |
    FunctionInvocation
;

    /*
       misc
            */
Epsilon:
;
%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.");

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        root->print();
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}

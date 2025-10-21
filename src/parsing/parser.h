#ifndef PARSER_H
#define PARSER_H

#include "token.h"

#include <stdbool.h>

struct ParamDecl
{
    const char* name;
    const char* data_type;
};

struct EntityName
{
    const char *name;
};

enum LiteralType
{
    LT_STRING = 1,
    LT_INT,
    LT_DOUBLE,
    LT_NULL,
};

struct Literal
{
    enum LiteralType type;
    const void      *value;
};

enum BinaryOperator {
    OP_ADD = 1,      // +
    OP_SUB,          // -
    OP_MUL,          // *
    OP_DIV,          // /
    OP_EQUALS,       // ==
    OP_NOT_EQUALS,   // !=
    OP_LESS_THAN,    // <
    OP_GREATER_THAN, // >
    OP_ASSIGN        // =
};

enum AstNodeType
{
    AST_FUNCTION_DECLARATION = 1,
    AST_PARAMETER_DECLARATION,
    AST_VARIABLE_DECLARATION,

    AST_CALL_EXPRESSION,
    AST_VARIABLE_EXPRESSION,
    AST_BLOCK,
    AST_MEMBER_ACCESS,
    AST_CAST,

    AST_ROOT,
};

union Value;

enum ValueType
{
    VAL_ENTITY = 1,
    VAL_MEMBER,
    VAL_LITERAL,
    VAL_CALL
};

struct BinaryExpr
{
    enum BinaryOperator op;

    enum ValueType left_type;
    union Value   *left_val;

    enum ValueType right_type;
    union Value   *right_val;
};

struct VarDecl
{
    const char      *name;
    const char      *data_type;
    enum AstNodeType init_type;

    union
    {
        struct EntityName var_expr;
        struct Literal    literal;
        struct BinaryExpr binary;
    };
};

struct MemberExpr
{
    bool is_var_owner;
    union
    {
        struct EntityName  variable_owner;
        struct MemberExpr *member_owner;
    };

    struct EntityName var;
};

struct CallExpr;

union Value
{
    struct EntityName var;
    struct MemberExpr member;
    struct Literal    literal;
    struct CallExpr  *call;
};

struct CallExpr
{
    bool is_var;
    union
    {
        struct EntityName var;
        struct MemberExpr member;
    };

    size_t       argc;
    union Value *arguments;
};

struct EntityAssign
{
    bool is_assignee_entity;
    union
    {
        struct EntityName assignee_entity;
        struct MemberExpr assignee_member;
    };

    enum ValueType value_type;
    union Value    value;
};

struct AstNode;

struct IfStmt
{
    enum ValueType condition_type;
    union Value    condition;
};

union Instruction
{
    struct CallExpr     call_expr;
    struct IfStmt       if_stmt;
    struct VarDecl      var_decl;
    struct EntityAssign assignment;
};

enum InstructionType
{
    IST_CALL = 1,
    IST_IF,
    IST_VARDECL,
    IST_ASSIGN
};

struct Block
{
    size_t                count;
    enum InstructionType *types;
    union Instruction    *instructions;
};

struct FuncDecl
{
    const char       *name;
    size_t            paramsc;
    struct ParamDecl *parameters;
    const char       *return_type;
    struct Block      body;
};

struct ClassDecl 
{

};

enum DeclType 
{
    DT_FUNC_DECL = 1,
    DT_VAR_DECL,
    DT_CLASS_DECL
};

union Decl
{
    struct FuncDecl  func_decl;
    struct VarDecl   var_decl;
    struct ClassDecl class_decl;
};

struct Program
{
    size_t        decls_count;
    enum DeclType types;
    union Decl   *decls;
};

struct AstNode
{
    enum AstNodeType node_type;
    union
    {
        struct FuncDecl   func_decl;
        struct VarDecl    var_decl;
        struct EntityName var_expr;
        struct BinaryExpr binary_expr;
        struct Literal    literal;
        struct CallExpr   call;
    };
};

typedef enum ParseErrorType
{
    UNEXPECTED_TOKEN = 1,
} ParseErrorType;

int
parse(const char *code, struct AstNode *out_node);

int
parse_func_decl(const struct Token *tokens,
                size_t              tokens_count,
                size_t             *pos,
                struct FuncDecl    *out_func_decl);

int
parse_block(const struct Token *tokens, size_t tokens_count, size_t *pos, struct Block *out_block);

struct Token*
tokenize(const char* code, size_t* out_count);


#endif
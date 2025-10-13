#ifndef PARSER_H
#define PARSER_H

#include "token.h"

#include <stdbool.h>

struct ParameterDeclaration {
    const char* name;
    const char* data_type;
};

struct FunctionDeclaration {
    const char* name;
    size_t paramsc;
    struct ParameterDeclaration* parameters;
    const char* return_type;
};

struct EntityExpression {
    const char* name;
};

enum LiteralType {
    LT_STRING = 1,
    LT_INT,
    LT_DOUBLE,
    LT_NULL,
};

struct Literal {
    enum LiteralType type;
    const void* value;
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

enum AstNodeType {
    FUNCTION_DECLARATION = 1,
    PARAMETER_DECLARATION,
    VARIABLE_DECLARATION,

    CALL_EXPRESSION,
    VARIABLE_EXPRESSION,
    BLOCK,
    MEMBER_ACCESS,
    CAST,

};

union Value;

enum ValueType {
    VAL_ENTITY = 1,
    VAL_MEMBER,
    VAL_LITERAL,
    VAL_CALL
};

struct BinaryExpression {
    enum BinaryOperator op;
    
    enum ValueType left_type;
    union Value* left_val;
    
    enum ValueType right_type;
    union Value* right_val;
};

struct VariableDeclaration {
    const char* name;
    const char* data_type;
    enum AstNodeType init_type;
    union {
        struct EntityExpression* var_expr;
        struct Literal literal;
        struct BinaryExpression binary;
    };
};

struct MemberExpression {
    bool is_var_owner;
    union {
        struct EntityExpression variable_owner;
        struct MemberExpression* member_owner;
    };

    struct EntityExpression var; 
};

struct CallExpression;

union Value {
    struct EntityExpression var;
    struct MemberExpression member;
    struct Literal literal;
    struct CallExpression* call;
};

struct CallExpression {
    bool is_var;
    union {
        struct EntityExpression var;
        struct MemberExpression member;
    }; 

    size_t argc;
    union Value* arguments;
};

struct EntityAssignment {
    bool is_assignee_entity;
    union {
        struct EntityExpression assignee_entity;
        struct MemberExpression assignee_member;
    };
    
    enum ValueType value_type;
    union Value value;
};

struct AstNode;
struct IfStatement;

union Instruction {
    struct CallExpression call_expr;
    struct IfStatement* if_stmt;
    struct VariableDeclaration var_decl;
    struct EntityAssignment assignment;
};

enum InstructionType {
    IST_CALL = 1,
    IST_IF,
    IST_VARDECL,
    IST_ASSIGN
};

struct Block {
    size_t count;
    enum InstructionType* types;
    union Instruction* instructions;
};

struct IfStatement {
    enum ValueType condition_type;
    union Value condition;
};

struct AstNode {
    enum AstNodeType node_type;
    union {
        struct FunctionDeclaration func_decl;
        struct VariableDeclaration var_decl;
        struct EntityExpression var_expr;
        struct BinaryExpression binary_expr;
        struct Literal literal;
        struct CallExpression call;
    };
};

typedef enum ParseErrorType {
    UNEXPECTED_TOKEN = 1,
} ParseErrorType;

struct Parser {
    const char* code;
    size_t current;
    size_t max;
    struct Token* tokens;
};

struct Token*
tokenize(const char* code, size_t* out_count);

int
parse(const char* code, struct AstNode* out_node);

#endif
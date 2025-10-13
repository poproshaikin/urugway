#ifndef TOKEN_H
#define TOKEN_H

#include <stddef.h>

enum TokenType {
    TT_IDENTIFIER = 1,

    TT_RETURN = 100,
    TT_CLASS,

    TT_INT = 200,
    TT_STRING,
    TT_FLOAT,
    TT_DOUBLE,
    TT_VOID,
    TT_NULL_,

    TT_SEMICOLON = 300,
    TT_PERIOD,
    TT_ASSIGN,
    TT_EQUALS,
    TT_MUL,
    TT_DIV,
    TT_PLUS,
    TT_MINUS,
    TT_LEFT_PAREN,
    TT_RIGHT_PAREN,
};

struct Token {
    enum TokenType type;
    const char* value;
    size_t line;
    size_t pos;
};

struct Token
make_token(enum TokenType type, const char* value, size_t line, size_t pos);

#endif
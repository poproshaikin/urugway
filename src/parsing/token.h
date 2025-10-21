#ifndef TOKEN_H
#define TOKEN_H

#include <stdbool.h>
#include <stddef.h>

enum TokenType
{
    TT_IDENTIFIER = 1,

    TT_LITERALS_SECTION_START = 200,

    TT_STRING_LITERAL,
    TT_INT_LITERAL,
    TT_DOUBLE_LITERAL,
    TT_FLOAT_LITERAL,

    TT_LITERALS_SECTION_END = 299,
    TT_KEYWORD_SECTION_START = 300,

    TT_INT,
    TT_STRING,
    TT_FLOAT,
    TT_DOUBLE,
    TT_VOID,
    TT_NULL_,
    TT_RETURN,
    TT_CLASS,

    TT_KEYWORD_SECTION_END = 399,
    // -- SYMBOLS --
    TT_SYMBOLS_SECTION_START = 400,

    TT_SEMICOLON,
    TT_PERIOD,
    TT_COMMA,
    TT_LEFT_PAREN,
    TT_RIGHT_PAREN,
    TT_LEFT_CURLY,
    TT_RIGHT_CURLY,

    TT_SYMBOLS_SECTION_END = 499,
    // -- OPERATORS -- 
    TT_OPERATORS_SECTION_START = 500,

    TT_ASSIGN,
    TT_EQUALS,
    TT_INEQUALS,
    TT_MUL,
    TT_DIV,
    TT_PLUS,
    TT_MINUS,
    TT_AMPERSAND,
    TT_PIPE,
    TT_AND,
    TT_OR,

    TT_OPERATORS_SECTION_END = 599,
};

struct Token
{
    enum TokenType type;
    const char    *value;
    size_t         line;
    size_t         pos;
};

struct Token
make_token(enum TokenType type, const char *value, size_t line, size_t pos);

bool
is_keyword(const struct Token *token);
bool
is_symbol(const struct Token *token);
bool
is_operator(const struct Token *token);

bool 
can_be_entity_name(const struct Token* token);

#endif
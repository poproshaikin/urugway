#include "token.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct Token
make_token(enum TokenType type, const char *value, size_t line, size_t pos)
{
    size_t val_len  = strlen(value);
    char  *val_copy = malloc(val_len + 1);
    memcpy(val_copy, val_copy, val_len + 1);

    return (struct Token){.type = type, .value = val_copy, .line = line, .pos = pos};
}

bool
is_keyword(const struct Token *token) 
{
    return token->type > TT_KEYWORD_SECTION_START && token->type < TT_KEYWORD_SECTION_END;
}

bool
is_symbol(const struct Token* token) 
{
    return token->type > TT_SYMBOLS_SECTION_START && token->type < TT_SYMBOLS_SECTION_END;
}

bool
is_operator(const struct Token* token) 
{
    return token->type > TT_OPERATORS_SECTION_START && token->type < TT_OPERATORS_SECTION_END;
}

bool 
can_be_type_name(const struct Token *token) 
{
    return !is_keyword(token) && !is_symbol(token) && !is_operator(token);
}
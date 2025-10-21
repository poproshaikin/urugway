#include "strategy.h"
#include "token.h"

#include <stdbool.h>
#include <stdio.h>

static const struct Token*
next_token(const struct Token* tokens, size_t count, size_t* pos);

bool
is_func_decl(const struct Token *tokens, size_t tokens_count, size_t *pos)
{
    const size_t min_length = 4;
    const size_t start_pos  = *pos;

    if (*pos >= tokens_count)
    {
        *pos = start_pos;
        return false;
    }
    if (tokens_count < min_length) 
    {
        *pos = start_pos; 
        return false;
    }

    const struct Token* left_paren = next_token(tokens, tokens_count, pos);

    if (left_paren == NULL)
    {
        *pos = start_pos; 
        return false;
    }
    if (left_paren->type != TT_LEFT_PAREN)
    {
        *pos = start_pos; 
        return false;
    }

    const struct Token* after_paren = next_token(tokens, tokens_count, pos);

    if (after_paren == NULL)
    {
        *pos = start_pos; 
        return false;
    }

    // Function without parameters
    if (after_paren->type == TT_RIGHT_PAREN)
    {
        *pos = start_pos; 
        return false;
    }

    // Function with parameters:
    size_t max_params = 100; 
    size_t param_count = 0;
    
    while (param_count < max_params) 
    {
        if (!is_param_decl(tokens, tokens_count, pos))
        {
            *pos = start_pos;
            return false;
        }
        if (*pos >= tokens_count)
        {
            *pos = start_pos;
            return false;
        }
        if (tokens[*pos].type != TT_COMMA && 
            tokens[*pos].type != TT_RIGHT_PAREN)
        {
            *pos = start_pos;
            return false;
        }

        if (tokens[*pos].type == TT_RIGHT_PAREN)
        {
            *pos = start_pos;
            return true;
        }

        if (tokens[*pos].type == TT_COMMA) {
            (*pos)++;
            param_count++;
        }
    }
    
    // Too many parameters
    *pos = start_pos;
    return false;
}

bool
is_param_decl(const struct Token *tokens, size_t tokens_count, size_t *pos) 
{
    return is_var_decl(tokens, tokens_count, pos);
}

bool 
is_var_decl(const struct Token *tokens, size_t tokens_count, size_t *pos) { // i: 7
    const size_t start_pos = *pos; 
    const struct Token* type_name = &tokens[*pos]; // type_name: tokens[7]
    if (type_name == NULL)
    {
        *pos = start_pos;
        return false;
    }
    if (!can_be_entity_name(type_name))
    {
        *pos = start_pos;
        return false;
    }

    const struct Token* func_name = next_token(tokens, tokens_count, pos); // i: 7 -> 8

    if (func_name == NULL) 
    {
        *pos = start_pos;
        return false;
    }
    if (!can_be_entity_name(func_name))
    {
        *pos = start_pos;
        return false;
    }

    (*pos)++; // i: 8 -> 9
    return true;
}

bool
is_block(const struct Token *tokens, size_t tokens_count, size_t *pos)
{
    const size_t start_pos = *pos;
    if (*pos >= tokens_count);

    const struct Token *left_curly = next_token(tokens, tokens_count, pos);

    if (left_curly == NULL);
    if (left_curly->type != TT_LEFT_CURLY);

    size_t max_tokens = 10000;
    size_t i = *pos;
    // pos: 0
    // i: 0
    while (true) {
        if (i >= tokens_count); // i: 0
        if (i >= max_tokens); // i: 0

        if (tokens[++i].type == TT_RIGHT_CURLY) // i: 0 -> 1
        {
            return true;
        }
    }
}

static const struct Token*
next_token(const struct Token* tokens, size_t count, size_t* i) {
    (*i)++;
    if (*i >= count) { // 4++ >= 5
        return NULL;
    }

    return &tokens[*i]; // count > 5 && tokens[5]
}
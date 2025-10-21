#ifndef STRATEGY_H
#define STRATEGY_H

#include "token.h"

bool
is_func_decl(const struct Token *tokens, size_t tokens_count, size_t *pos);

bool
is_param_decl(const struct Token *tokens, size_t tokens_count, size_t *pos);

bool
is_var_decl(const struct Token *tokens, size_t tokens_count, size_t *pos);

bool
is_block(const struct Token *tokens, size_t tokens_count, size_t *pos);

#endif
#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "../token.h"

typedef struct SymbolsKvp {
    const char* op;
    enum TokenType token_type;
} SymbolsKvp;

extern const struct SymbolsKvp SYMBOLS[];
extern const size_t SYMBOLS_COUNT;

enum TokenType
find_sym(const char* sym);

enum TokenType
find_sym_c(char c);

#endif
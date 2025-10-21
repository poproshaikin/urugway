#include "symbols.h"

#include <string.h>
#include <stdlib.h>

const struct SymbolsKvp SYMBOLS[] = {
    {".", TT_PERIOD },
    {",", TT_COMMA },
    {";", TT_SEMICOLON },
    {"(", TT_LEFT_PAREN },
    {")", TT_RIGHT_PAREN },
    {"{", TT_LEFT_CURLY },
    {"}", TT_RIGHT_CURLY },

};

const size_t SYMBOLS_COUNT = sizeof(SYMBOLS) / sizeof(SYMBOLS[0]);

enum TokenType
find_sym(const char* sym) {
    for (size_t i = 0; i < SYMBOLS_COUNT; i++) {
        if (strcmp(sym, SYMBOLS[i].op) == 0) {
            return SYMBOLS[i].token_type;
        }
    }
    return 0;
}

enum TokenType
find_sym_c(char c) {
    char* str = malloc(2);
    str[0] = c;
    str[1] = '\0';
    enum TokenType type = find_sym(str);
    free(str);
    return type;
}
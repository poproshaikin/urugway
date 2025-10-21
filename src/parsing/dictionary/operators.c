#include "operators.h"
#include <string.h>

const struct OperatorsKvp OPERATORS[] = {
    { "*",  TT_MUL },
    { "+",  TT_PLUS },
    { "-",  TT_MINUS },
    { "/",  TT_DIV },
    { "&",  TT_AMPERSAND },
    { "&&", TT_AND },
    { "|",  TT_PIPE },
    { "||", TT_OR },
    { "=",  TT_ASSIGN },
    { "==", TT_EQUALS },
    { "!=", TT_INEQUALS },
};

const size_t OPERATORS_COUNT = sizeof(OPERATORS) / sizeof(OPERATORS[0]);

const size_t MAX_OPERATOR_LEN = 2;

enum TokenType
find_op(const char* lexeme) {
    for (size_t i = 0; i < OPERATORS_COUNT; i++) {
        if (strcmp(lexeme, OPERATORS[i].op) == 0) {
            return OPERATORS[i].token_type;
        }
    }
    return 0;
}
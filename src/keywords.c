#include "keywords.h"
#include "token.h"

#include <string.h>

const struct KeywordKvp KEYWORDS[] = {
    { "return", TT_RETURN },
    { "class",  TT_CLASS },
    { "int",    TT_INT },
    { "string", TT_STRING },
    { "float",  TT_FLOAT },
    { "double", TT_DOUBLE },
    { "void",   TT_VOID },
    { "null",   TT_NULL_ },
};

const size_t KEYWORDS_COUNT = sizeof(KEYWORDS) / sizeof(KEYWORDS[0]);

enum TokenType
find_kw(const char* lexeme) {
    for (size_t i = 0; i < KEYWORDS_COUNT; i++) {
        if (strcmp(lexeme, KEYWORDS[i].keyword) == 0) {
            return KEYWORDS[i].token_type;
        }
    }
    return 0;
}
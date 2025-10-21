#ifndef KEYWORDS_H
#define KEYWORDS_H

#include "../token.h"

struct KeywordKvp {
    const char* keyword;
    enum TokenType token_type;
};

extern const struct KeywordKvp KEYWORDS[];
extern const size_t KEYWORDS_COUNT;

enum TokenType 
find_kw(const char* lexeme);

#endif
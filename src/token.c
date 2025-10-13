#include "token.h"

struct Token
make_token(enum TokenType type, const char* value, size_t line, size_t pos) {
    return (struct Token){
        .type = type,
        .value = value,
        .line = line,
        .pos = pos
    };
}

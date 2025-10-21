#ifndef OPERATORS_H
#define OPERATORS_H

#include "../token.h"

typedef struct OperatorsKvp {
    const char* op;
    enum TokenType token_type;
} OperatorsKvp;

extern const struct OperatorsKvp OPERATORS[];
extern const size_t OPERATORS_COUNT;
extern const size_t MAX_OPERATOR_LEN;

enum TokenType
find_op(const char* op);

#endif
#include "parser.h"
#include "../utils.h"
#include "dictionary/keywords.h"
#include "dictionary/operators.h"
#include "dictionary/symbols.h"
#include "strategy.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool
is_alpha(char c);
static bool
is_digit(char c);
static bool
is_space(char c);
static bool
starts_as_operator(char c);

static char *
to_lower(char *str);

static size_t
number_len(const char *str);
static size_t
next_word_len(const char *str);
static char *
read_next_word(const char *code, size_t i);
static void
push_token(struct Token **tokens, struct Token token, size_t *out_count);

int
parse(const char *code, struct AstNode *out_node)
{
    size_t        count;
    struct Token *tokens = tokenize(code, &count);
    if (!tokens)
    {
        fprintf(stderr, "Failed to tokenize code\n");
        return 1;
    }

    struct AstNode root = { .node_type = AST_ROOT, };

    size_t pos = 0;
    if (is_func_decl(tokens, count, &pos))
    {
        parse_func_decl(tokens, count, &pos);

    }

    return 0;
}

int
parse_func_decl(const struct Token *tokens,
                size_t              tokens_count,
                size_t             *pos,
                struct FuncDecl    *out_func_decl)
{
    struct FuncDecl func_decl;
    size_t          block_end = 0;

    if (is_block(tokens, tokens_count, pos))
    {
        struct Block body;
        parse_block(tokens, tokens_count, pos, &body);
    }
    else 
    {
    
    }
}

int 
parse_block(const struct Token *tokens, size_t tokens_count, size_t *pos, struct Block *out_block) 
{
    
}

struct Token *
tokenize(const char *code, size_t *out_count)
{
    size_t line = 1;
    size_t pos  = 0;

    size_t i = 0;

    size_t        tokens_count = 0;
    struct Token *tokens       = malloc(sizeof(struct Token));

    while (i < strlen(code))
    {
        char c = code[i];

        if (is_space(c))
        {
            if (c == '\n')
            {
                line++;
                pos = 0;
            }
            else
            {
                pos++;
            }
            i++;
            continue;
        }
        else if (isalpha(c))
        {
            char        *next_word = read_next_word(code, i);
            char        *word      = to_lower(next_word);
            struct Token token     = make_token(TT_IDENTIFIER, word, line, pos);

            enum TokenType type = find_kw(word);
            if (type != 0)
            {
                token.type = type;
            }

            push_token(&tokens, token, &tokens_count);
            pos += strlen(word);
            i += strlen(word);

            free(next_word);
            free(word);
        }
        else if (c == '"')
        {
            size_t word_start = i + 1;
            size_t word_end   = find_in_str('"', &code[word_start]);

            if (word_end == -1)
            {
                free(tokens);
                fprintf(stderr, "tokenize: unterminated string literal\n");
                return NULL;
            }

            char        *word  = substr(code, word_start, word_end - word_start);
            struct Token token = make_token(TT_STRING_LITERAL, word, line, pos);

            push_token(&tokens, token, &tokens_count);

            size_t consumed = (word_end + 1) - i;
            i += consumed;
            pos += consumed;

            free(word);
        }
        else if (is_digit(c))
        {
            size_t word_start = i;
            size_t word_len   = number_len(&code[i]);

            char *word         = substr(code, word_start, word_len);
            bool  contains_dot = find_in_str('.', word) != -1;
            bool  contains_f   = find_in_str('f', word) != -1 || find_in_str('F', word) != -1;
            bool  contains_d   = find_in_str('d', word) != -1 || find_in_str('D', word) != -1;

            enum TokenType token_type;
            if (contains_f)
                token_type = TT_FLOAT_LITERAL;
            else if (contains_d || contains_dot)
                token_type = TT_DOUBLE_LITERAL;
            else
                token_type = TT_INT_LITERAL;

            struct Token token = make_token(token_type, word, line, pos);
            push_token(&tokens, token, &tokens_count);

            i += word_len;
            pos += word_len;

            free(word);
        }
        else if (starts_as_operator(c))
        {
            size_t         op_start = i;
            char          *op       = NULL;
            enum TokenType op_type;

            size_t max_len = MAX_OPERATOR_LEN;
            while (max_len > 0 && op_start + max_len <= strlen(code))
            {
                char *candidate_mixed_case = substr(code, op_start, max_len);
                char *candidate_lower_case = to_lower(candidate_mixed_case);
                free(candidate_mixed_case);
                ssize_t op_pos = find_op(candidate_lower_case);
                if (op_pos != -1)
                {
                    op      = candidate_lower_case;
                    op_type = OPERATORS[op_pos].token_type;
                    break;
                }
                free(candidate_lower_case);
                max_len--;
            }

            if (op == NULL)
            {
                fprintf(stderr, "tokenize: unknown operator at position %lu", pos);
                free(tokens);
                return NULL;
            }

            struct Token token = make_token(op_type, op, line, pos);
            free(op);
            push_token(&tokens, token, &tokens_count);

            i += strlen(op);
            pos += strlen(op);
        }
        else if (find_sym_c(c) != -1)
        {
            char *sym_str           = malloc(2);
            sym_str[0]              = c;
            sym_str[1]              = '\0';
            enum TokenType sym_type = find_sym_c(c);
            struct Token   token    = make_token(sym_type, sym_str, line, pos);
            push_token(&tokens, token, &tokens_count);

            i++;
            pos++;
        }
    }

    *out_count = tokens_count;
    return tokens;
}

static size_t
next_word_len(const char *str)
{
    const char *p = str;

    while (*p != '\0' && (isalnum(*p) || *p == '_'))
    {
        ++p;
    }

    return p - str;
}

static size_t
number_len(const char *str)
{
    const char *p         = str;
    bool        dot_found = false;

    while (is_digit(*p) || (!dot_found && *p == '.'))
    {
        if (*p == '.')
            dot_found = true;
        ++p;
    }

    if (*p == 'f' || *p == 'F' || *p == 'd' || *p == 'D')
    {
        ++p;
    }

    return p - str;
}

static char *
read_next_word(const char *code, size_t i)
{
    size_t word_start = i;
    size_t word_len   = next_word_len(&code[i]);

    char *word = malloc(word_len + 1);
    memcpy(word, &code[word_start], word_len);
    word[word_len] = '\0';
    return word;
}

static bool
starts_as_operator(char c)
{
    for (size_t i = 0; i < OPERATORS_COUNT; i++)
    {
        if (OPERATORS[i].op[0] == c)
        {
            return true;
        }
    }
    return false;
}

static void
push_token(struct Token **tokens, struct Token token, size_t *out_count)
{
    if (!tokens || !out_count)
    {
        fprintf(stderr, "push_token: null argument\n");
    }

    size_t new_count = *out_count + 1;

    struct Token *new_tokens = realloc(*tokens, new_count * sizeof(struct Token));
    if (!new_tokens)
    {
        fprintf(stderr, "push_token: realloc failed\n");
        return;
    }

    new_tokens[new_count - 1] = token;

    *tokens    = new_tokens;
    *out_count = new_count;
}

static char *
to_lower(char *str)
{
    size_t len = strlen(str);
    char  *new = malloc(len);
    for (size_t i = 0; i < len; i++)
    {
        new[i] = tolower(str[i]);
    }
    return str;
}

static bool
is_alpha(char c)
{
    return isalpha((unsigned char)c) || (unsigned char)c == '_';
}

static bool
is_digit(char c)
{
    return isdigit((unsigned char)c);
}

static bool
is_space(char c)
{
    return isspace((unsigned char)c);
}

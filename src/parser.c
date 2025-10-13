#include "parser.h"
#include "keywords.h"
#include "utils.h"

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool is_alpha(char c) {
    return isalpha((unsigned char)c) || (unsigned char)c == '_';
}

bool is_digit(char c) {
    return isdigit((unsigned char)c);
}

bool is_space(char c) {
    return isspace((unsigned char)c);
}

size_t
next_word_len(const char* str) {
    const char* p = str;

    while (*p != '\0' && (isalnum(*p) || *p == '_')) {
        ++p;
    }

    return p - str;
}

char*
read_next_word(const char* code, size_t i) {
    size_t word_start = i; 
    size_t word_len = next_word_len(&code[i]); 

    char* word = malloc(word_len + 1); 
    memcpy(word, &code[word_start], word_len);
    word[word_len] = '\0';  
    return word;
}

// Returns pointer to self
char*
to_lower(char* str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
    return str;
}

void
push_token(struct Token** tokens, struct Token token, size_t* out_count) {
    if (!tokens || !out_count) {
        fprintf(stderr, "push_token: null argument\n");
    }

    size_t new_count = *out_count + 1;

    struct Token* new_tokens = realloc(*tokens, new_count * sizeof(struct Token));
    if (!new_tokens) {
        fprintf(stderr, "push_token: realloc failed\n");
        return;
    }

    new_tokens[new_count - 1] = token;

    *tokens = new_tokens;
    *out_count = new_count;
}

struct Token*
tokenize(const char* code, size_t* out_count) {
    size_t line = 1;
    size_t pos = 0;

    size_t i = 0;

    size_t tokens_count = 0;
    struct Token* tokens = malloc(sizeof(struct Token));

    while (i < strlen(code)) {
        char c = code[i];

        if (is_space(c)) {
            if (c == '\n') {
                line++;
                pos = 0;
            } 
            else {
                pos++;
            }
            i++;
            continue;
        }
        else if (isalpha(c)) {
            char* word = to_lower(read_next_word(code, i));
            struct Token token = make_token(TT_IDENTIFIER, word, line, pos);

            enum TokenType type = find_kw(word);
            if (type != 0) {
                token.type = type;
            }

            push_token(&tokens, token, &tokens_count);
            pos += strlen(word);
            i += strlen(word);
        }
        
        i++;
    }
    
    *out_count = 0;  
    return NULL;     
}

int
parse(const char* code, struct AstNode* out_node) {
    size_t count;
    struct Token* tokens = tokenize(code, &count);
    if (!tokens) {
        fprintf(stderr, "Failed to tokenize code\n");
        return 1;
    }

    // TODO: реализовать парсинг
    return 0;  // пока что успешное завершение
}
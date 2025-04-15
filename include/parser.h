/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#ifndef PARSER_H_
    #define PARSER_H_

    #include <stdlib.h>
// ? Token types for our parser
typedef enum token_type_s {
    TT_SMCL,            // ? 0: ';'
    TT_NEWLINE,         // ? 1: '\n'
    TT_PIPE,            // ? 2: '|'
    TT_AND,             // ? 3: '&&'
    TT_OR,              // ? 4: '||'
    TT_JOB,             // ? 5: '&'
    TT_REDIRECT_OUT,    // ? 6: '>'
    TT_APPEND,          // ? 7: '>>'
    TT_REDIRECT_IN,     // ? 8: '<'
    TT_HEREDOC,         // ? 9: '<<'
    TT_BACKTICK,        // ? 10: '`'
    TT_RAW_STRING,      // ? 11: "'" [char]* "'"
    TT_LPAREN,          // ? 12: '('
    TT_RPAREN,          // ? 13: ')'
    TT_WORD,            // ? 14: Generic word (e.g., command names)
    TT_EOF,             // ? 15: '\0' End of input
    NB_TOKENS           // ? 16: Count of tokens (not an actual token)
} token_type_t;

typedef struct lexer_s {
    const char *start;
    size_t pos;
} lexer_t;

extern const char *tokens_list[NB_TOKENS];

typedef struct token_s {
    token_type_t type;
    char *value;
    size_t len;
} token_t;


#endif /* !PARSER_H_ */

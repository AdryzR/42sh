/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include "lexer.h"
#include <stdbool.h>

const char *token_list[NB_TOKENS] = {
    [TT_SMCL] = "Semicolon",
    [TT_NEWLINE] = "Newline",
    [TT_PIPE] = "|",
    [TT_AND] = "&&",
    [TT_OR] = "||",
    [TT_JOB] = "&",
    [TT_REDIRECT_OUT] = ">",
    [TT_APPEND] = ">>",
    [TT_REDIRECT_IN] = "<",
    [TT_HEREDOC] = "<<",
    [TT_BACKTICK] = "`",
    [TT_RAW_STRING] = "'",
    [TT_LPAREN] = "(",
    [TT_RPAREN] = ")",
    [TT_WORD] = NULL,
    [TT_EOF] = NULL,
};

/*
** Return a generic token filled with the type and the lenght given in args.
*/
token_t make_generic(lexer_t *lexer, token_type_t type, size_t length)
{
    lexer->pos = length;
    return (token_t) {
        .type = type,
        .value = lexer->start,
        .len = lexer->pos
    };
}

bool is_eol(lexer_t *lexer)
{
    return
        lexer->start[lexer->pos] == '\0' ||
        lexer->start[lexer->pos] == '\n';
}

token_t make_string(lexer_t *lexer, char c, token_type_t type)
{
    lexer->pos++;
    while (lexer->start[lexer->pos] != c && !is_eol(lexer))
        lexer->pos++;
    if (lexer->start[lexer->pos] != c)
        return (token_t){ .type = TT_ERROR };
    lexer->pos++;
    return (token_t) {
        .type = type,
        .value = lexer->start + 1,
        .len = lexer->pos - 2,
    };
}

token_t make_word_token(lexer_t *lexer)
{
    while (!is_reserved_char(lexer->start[lexer->pos]))
        lexer->pos++;
    return (token_t) {
        .type = TT_WORD,
        .value = lexer->start,
        .len = lexer->pos
    };
}

static token_t get_other_token(lexer_t *lexer)
{
    switch (*lexer->start) {
    case '\n':
        return make_generic(lexer, TT_NEWLINE, 1);
    case '`':
        return make_string(lexer, '`', TT_BACKTICK);
    case '\'':
        return make_string(lexer, '\'', TT_RAW_STRING);
    case '"':
        return make_string(lexer, '"', TT_WORD);
    case '(':
        return make_generic(lexer, TT_LPAREN, 1);
    case ')':
        return make_generic(lexer, TT_RPAREN, 1);
    case '\0':
        return make_generic(lexer, TT_EOF, 1);
    default:
        return make_word_token(lexer);
    }
}

static token_t get_redirect_token(lexer_t *lexer)
{
    switch (*lexer->start) {
    case '>':
        return *(lexer->start + 1) == '>' ?
            make_generic(lexer, TT_APPEND, 2) :
                make_generic(lexer, TT_REDIRECT_OUT, 1);
    case '<':
        return *(lexer->start + 1) == '<' ?
            make_generic(lexer, TT_HEREDOC, 2) :
                make_generic(lexer, TT_REDIRECT_IN, 1);
    default:
        return get_other_token(lexer);
    }
}

//* init lexer->pos et start à 0 avant
token_t get_next_token(lexer_t *lexer)
{
    lexer->start += lexer->pos;
    lexer->pos = 0;
    skip_whitespace(lexer);
    if (*lexer->start == '\0')
        return (token_t){ .type = TT_EOF };
    switch (*lexer->start) {
    case '|':
        return *(lexer->start + 1) == '|' ?
            make_generic(lexer, TT_OR, 2) : make_generic(lexer, TT_PIPE, 1);
    case '&':
        return *(lexer->start + 1) == '&' ?
            make_generic(lexer, TT_AND, 2) : make_generic(lexer, TT_JOB, 1);
    case ';':
        return make_generic(lexer, TT_SMCL, 1);
    case '\n':
        return make_generic(lexer, TT_NEWLINE, 1);
    default:
        return get_redirect_token(lexer);
    }
}

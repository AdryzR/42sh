/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser
*/

#include "parser.h"
#include <stdbool.h>

const char *token_list[NB_TOKENS] = {
    [TT_SMCL] = ";",
    [TT_NEWLINE] = "\n",
    [TT_PIPE] = "|",
    [TT_AND] = "&&",
    [TT_OR] = "||",
    [TT_JOB] = "&",
    [TT_REDIRECT_OUT] = ">",
    [TT_APPEND] = ">>",
    [TT_REDIRECT_IN] = "<<",
    [TT_HEREDOC] = "<<",
    [TT_BACKTICK] = "`",
    [TT_RAW_STRING] = "'",
    [TT_LPAREN] = "(",
    [TT_RPAREN] = "(",
    [TT_WORD] = NULL,
    [TT_EOF] = NULL,
};

bool is_whitespace(char c)
{
    return
        c == '\0' ||
        c == '\t' ||
        c == ' ';
}

void skip_whitespace(lexer_t *lexer)
{
    while (*lexer->start != '\0' && is_whitespace(*lexer->start))
        lexer->start++;
}

//* ls bob 

token_t get_word_token(lexer_t *lexer)
{
    while (!is_whitespace(lexer->start[lexer->pos]))
        lexer->pos++;
    return (token_t){
        .type = TT_WORD,
        .value = lexer->start,
        .len = lexer->pos
    };
}

token_t make_generic(lexer_t *lexer, token_type_t type, size_t length)
{
    return (token_t){
        .type = type,
        .value = lexer->start,
        .len = length
    };
}

token_t get_other_token(lexer_t *lexer)
{
    switch (*lexer->start)
    {
    case constant expression:
        /* code */
        break;
    
    default:
        break;
    }
}

token_t get_redirect_token(lexer_t *lexer)
{
    switch (*lexer->start)
    {
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

token_t get_next_token(lexer_t *lexer)
{
    lexer->pos = 0;
    skip_whitespace(lexer);
    switch (*lexer->start) {
    case '|':
        return *(lexer->start + 1) == '|' ?
            make_generic(lexer, TT_OR, 2) : make_generic(lexer, TT_PIPE, 1);
    case '&':
        return *(lexer->start + 1) == '&' ?
            make_generic(lexer, TT_JOB, 1) : make_generic(lexer, TT_AND, 2);
    case ';':
        return make_generic(lexer, TT_SMCL, 1);
    case '\n':
        return make_generic(lexer, TT_NEWLINE, 1);
    default:
        return get_redirect_token(lexer);
        // return get_word_token(lexer);
    }
}

// main:
// parse_input(readline(stdin))
// free(parse_input)
// 
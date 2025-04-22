/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** utilities
*/

#include <lexer.h>
#include <string.h>

static const char reserved_chars[] = {
    '&', '|', '>', '<',  // ? operators
    '(', ')',            // ? parentheses
    ';', '\n',           // ? separators
    '\0',
};

bool is_whitespace(char c)
{
    return
        c == '\0' ||
        c == '\t' ||
        c == ' ';
}

bool is_reserved_char(char c)
{
    const char *current = reserved_chars;

    if (is_whitespace(c))
        return true;
    while (*current != '\0') {
        if (c == *current)
            return true;
        current++;
    }
    return false;
}

void skip_whitespace(lexer_t *lexer)
{
    while (*lexer->start != '\0' && is_whitespace(*lexer->start))
        lexer->start++;
}

char *get_token_value(const token_t *token)
{
    return strndup(token->value, token->type);
}
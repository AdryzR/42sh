/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** replace_aliases
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "my_sh.h"

static bool alias_exists(alias_t *head, const char *name, size_t len)
{
    for (; head; head = head->next)
        if (head->name && strlen(head->name) == len
         && !strncmp(head->name, name, len))
            return true;
    return false;
}

static const char *alias_get(alias_t *head, const char *name, size_t len)
{
    for (; head; head = head->next)
        if (head->name && strlen(head->name) == len
         && !strncmp(head->name, name, len))
            return head->cmd;
    return NULL;
}

static void ensure_capacity(char **buffer, size_t *capacity, char **cursor, size_t need)
{
    size_t used = *cursor - *buffer;
    if (used + need > *capacity) {
        *capacity = (*capacity * 2) + need;
        *buffer = realloc(*buffer, *capacity);
        *cursor = *buffer + used;
    }
}

static void append_text(char **buffer, size_t *capacity, char **cursor,
    const char *text, size_t len)
{
    ensure_capacity(buffer, capacity, cursor, len + 2);
    memcpy(*cursor, text, len);
    *cursor += len;
    **cursor = ' ';
    (*cursor)++;
}

static void process_token(token_t tok, const char *input, alias_t *aliases,
    char **buffer, size_t *capacity, char **cursor)
{
    const char *token_start = tok.value;
    const char *replacement;
    size_t token_len = tok.len;
    bool is_quoted = (tok.type == TT_RAW_STRING)
                  || (tok.type == TT_BACKTICK)
                  || (token_start > input && token_start[-1] == '"');

    if (!is_quoted && tok.type == TT_WORD
     && alias_exists(aliases, token_start, token_len)) {
        replacement = alias_get(aliases, token_start, token_len);
        append_text(buffer, capacity, cursor, replacement, strlen(replacement));
    } else {
        if (is_quoted) { token_start--; token_len += 2; }
        append_text(buffer, capacity, cursor, token_start, token_len);
    }
}

char *replace_aliases(char *input, alias_t *aliases)
{
    lexer_t lexer;
    lexer.start = input;
    lexer.pos = 0;
    size_t capacity = strlen(input) * 2 + 1;
    char *result = malloc(sizeof(char) * (strlen(input) + 1));
    char *cursor = result;
    token_t tok;

    if (!result)
        return input;
    while ((tok = get_next_token(&lexer)).type != TT_EOF)
        process_token(tok, input, aliases, &result, &capacity, &cursor);
    if (cursor != result)
        *(cursor - 1) = '\0';
    else
        *cursor = '\0';
    return result;
}

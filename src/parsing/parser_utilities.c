/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parser_skip_separators
*/

#include <parser.h>

void parser_next(parser_t *parser)
{
    parser->prev = parser->current;
    parser->current = parser->next;
    parser->next = get_next_token(&parser->lexer);
}

void parser_skip_separators(parser_t *parser)
{
    parser_next(parser);
}


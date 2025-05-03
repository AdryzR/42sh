/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_expression
*/

#include <parser.h>

ast_t *parse_expression(parser_t *parser)
{
    if (parser->current.type == TT_LPAREN)
        return parse_parentheses(parser);
    return parse_command(parser);
}

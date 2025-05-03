/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_statement
*/

#include <parser.h>

//TODO: ajouter les if, while et foreach (scripting)
ast_t *parse_statement(parser_t *parser)
{
    return parse_binary_operation(parser);
}

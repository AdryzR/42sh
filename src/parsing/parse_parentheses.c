/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_parentheses
*/

#include <parser.h>

ast_t *parse_parentheses(parser_t *parser)
{
    ast_t *node = create_ast(AT_PAREN);
    ast_t *current;

    parser_next(parser);
    while (!is_paren_end(parser)) {
        current = parse_statement(parser);
        ast_list_append(&node->data.paren, current);
        while (parser->current.type == TT_SMCL)
            parser_next(parser);
    }
    if (parser->current.type != TT_RPAREN)
        parser->error_msg = "Too many ('s.";
    parser_next(parser);
    return node;
}

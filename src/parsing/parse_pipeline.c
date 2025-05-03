/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_pipeline
*/

#include <parser.h>

ast_t *parse_pipeline(parser_t *parser)
{
    ast_t *expr = parse_expression(parser);
    ast_t *node;

    if (parser->current.type != TT_PIPE)
        return expr;
    node = create_ast(AT_PIPELINE);
    ast_list_append(&node->data.pipeline, expr);
    while (parser->current.type == TT_PIPE) {
        parser_next(parser);
        expr = parse_expression(parser);
        ast_list_append(&node->data.pipeline, expr);
    }
    return node;
}

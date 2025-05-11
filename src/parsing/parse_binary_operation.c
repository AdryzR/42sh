/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_binary_operation
*/

#include <parser.h>

static ast_type_t get_operation_type(const parser_t *parser)
{
    switch (parser->current.type) {
    case TT_AND:
        return AT_AND;
    case TT_OR:
        return AT_OR;
    default:
        return AT_ERROR;
    }
}

ast_t *parse_binary_operation(parser_t *parser)
{
    ast_t *left = parse_pipeline(parser);
    ast_type_t op_type = get_operation_type(parser);
    ast_t *right;
    ast_t *operation;

    while (op_type != AT_ERROR) {
        parser_next(parser);
        right = parse_pipeline(parser);
        operation = create_ast(op_type);
        operation->data.binary_operation = malloc(sizeof(ast_t *) * 2);
        if (!operation->data.binary_operation) {
            parser->error_msg = "Malloc failed";
            return left;
        }
        operation->data.binary_operation[0] = left;
        operation->data.binary_operation[1] = right;
        left = operation;
        op_type = get_operation_type(parser);
    }
    return left;
}

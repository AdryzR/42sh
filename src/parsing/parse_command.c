/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parse_command
*/

#include <parser.h>

ast_t *return_ast_error(parser_t *parser)
{
    ast_t *error = create_ast(AT_ERROR);

    parser_next(parser);
    return error;
}

ast_t *parse_argument(parser_t *parser)
{
    ast_t *node = create_ast(AT_ARGUMENT);

    node->data.arg = get_token_value(&parser->current);
    parser_next(parser);
    return node;
}

ast_t *parse_command_node(parser_t *parser)
{
    if (is_a_redirect(parser))
        return parse_redirect(parser);
    return parse_argument(parser);
}

ast_t *parse_command(parser_t *parser)
{
    ast_t *node = create_ast(AT_COMMAND);
    ast_t *current;

    while (is_a_redirect(parser) || parser->current.type == TT_WORD) {
        current = parse_command_node(parser);
        ast_list_append(&node->data.command, current);
    }
    if (!contains_argument_node(node))
        parser->error_msg = "Invalid null command.";
    return node;
}

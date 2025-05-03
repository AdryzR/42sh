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
    while (IS_SEPARATOR(parser->current.type))
        parser_next(parser);
}

void ast_list_append(ast_list_t *list, ast_t *node)
{
    if (list->count == list->capacity) {
        list->capacity = list->capacity == 0 ? 4 : list->capacity * 1.5f;
        list->data = reallocarray(list->data, list->capacity, sizeof(ast_t *));
        if (list->data == NULL)
            return;
    }
    list->data[list->count] = node;
    list->count++;
}

bool contains_argument_node(const ast_t *node)
{
    for (size_t i = 0; i < node->data.command.count; i++)
        if (node->data.command.data[i]->type == AT_ARGUMENT)
            return true;
    return false;
}

parser_t *create_parser(void)
{
    static parser_t parser = { NULL };

    return &parser;
}

ast_t *create_ast(ast_type_t type)
{
    ast_t *ast = calloc(1, sizeof(ast_t));

    ast->type = type;
    return ast;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** create_ast
*/

#include <parser.h>

ast_t *create_ast(ast_type_t type)
{
    ast_t *ast = calloc(1, sizeof(ast_t));

    ast->type = type;
    return ast;
}

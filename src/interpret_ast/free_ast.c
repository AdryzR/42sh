/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** free_ast
*/

#include <interpreter.h>
#include <stdlib.h>

static void free_container(ast_t *ast)
{
    for (size_t i = 0; i < ast->data.program.count; i++)
        free_ast(ast->data.program.data[i]);
    free(ast->data.program.data);
}

static void free_binary_node(ast_t *ast)
{
    free_ast(ast->data.binary_operation[0]);
    free_ast(ast->data.binary_operation[1]);
    free(ast->data.binary_operation);
}

static void free_argument_node(ast_t *ast)
{
    free(ast->data.arg);
}

static void free_redirect_node(ast_t *ast)
{
    free(ast->data.redirect.path);
}

//! To implement if we add an error_node to the parser.
static void free_error_node(ast_t *ast)
{
    return;
}

void free_ast_node(ast_t *ast)
{
    if (!ast)
        return;
    switch (ast->type) {
    case AT_COMMAND:
    case AT_PIPELINE:
    case AT_PAREN:
    case AT_PROGRAM:
        return free_container(ast);
    case AT_AND:
    case AT_OR:
        return free_binary_node(ast);
    case AT_ARGUMENT:
        return free_argument_node(ast);
    case AT_REDIRECT:
        return free_redirect_node(ast);
    case AT_ERROR:
        return free_error_node(ast);
    }
}

void free_ast(ast_t *ast)
{
    free_ast_node(ast);
    free(ast);
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** print_ast
*/

#include "parser.h"
#include <stdio.h>

static void print_indent(unsigned short depth)
{
    for (unsigned short i = 0; i < depth; i++)
        printf("    ");
}

static void print_ast_node(const ast_t *ast, unsigned short depth);

static void print_ast_program(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    puts("Program Node:");
    for (size_t i = 0; i < ast->data.program.count; i++)
        print_ast_node(ast->data.program.data[i], depth + 1);
}

static void print_ast_paren(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    puts("Parentheses Node:");
    for (size_t i = 0; i < ast->data.paren.count; i++)
        print_ast_node(ast->data.paren.data[i], depth + 1);
}

static void print_ast_binary(const ast_t *ast, unsigned short depth, const char *op_name)
{
    print_indent(depth);
    printf("Binary Operation Node: %s\n", op_name);
    print_ast_node(ast->data.binary_operation[0], depth + 1);
    print_ast_node(ast->data.binary_operation[1], depth + 1);
}

static void print_ast_command(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    printf("Command Node\n");
    //TODO: Print the arguments of the command
}

static void print_ast_redirect(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    printf("Redirect Node: path=%s, type=%d\n", ast->data.redirect.path, ast->data.redirect.red_type);
}

static void print_ast_error(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    puts("AST ERROR");
    //TODO: add the type of error
}

static void print_ast_node(const ast_t *ast, unsigned short depth)
{
    if (!ast) return;

    switch (ast->type) {
        case AT_PROGRAM:
            print_ast_program(ast, depth);
            break;
        case AT_PAREN:
            print_ast_paren(ast, depth);
            break;
        case AT_PIPE:
            print_ast_binary(ast, depth, "PIPE");
            break;
        case AT_AND:
            print_ast_binary(ast, depth, "AND");
            break;
        case AT_OR:
            print_ast_binary(ast, depth, "OR");
            break;
        case AT_COMMAND:
            print_ast_command(ast, depth);
            break;
        case AT_REDIRECT:
            print_ast_redirect(ast, depth);
            break;
        case AT_ERROR:
            print_ast_error(ast, depth);
            break;
        default:
            print_indent(depth);
            puts("Error: Unknown AST Node Type");
            break;
    }
}

void print_ast(const ast_t *ast)
{
    print_ast_node(ast, 0);
}

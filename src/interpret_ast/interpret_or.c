/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_or
*/

#include <interpreter.h>

int interpret_or(const ast_t *ast, shell_t *shell)
{
    int status = 0;

    status = interpret(ast->data.binary_operation[0], shell);
    if (status == 0)
        return status;
    return interpret(ast->data.binary_operation[1], shell);
}

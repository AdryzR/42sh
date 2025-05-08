/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_program
*/

#include <my_sh.h>
#include <interpreter.h>

int interpret_program(const ast_t *ast, shell_t *shell)
{
    int status = 0;

    for (size_t i = 0; i < ast->data.program.count; i++)
        status = interpret(ast->data.program.data[i], shell);
    return status;
}

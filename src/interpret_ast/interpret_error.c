/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_error
*/

#include <my_sh.h>

int interpret_error(UNUSED const ast_t *ast, UNUSED shell_t *shell)
{
    dprintf(2, "Syntax error in AST\n");
    return 84;
}

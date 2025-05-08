/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpreter
*/

#include <interpreter.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>



static const interpret_fnc_t interpret_functions[AT_COUNT] = {
    [AT_ERROR] = interpret_error,
    [AT_COMMAND] = interpret_command,
    [AT_PROGRAM] = interpret_program,
    [AT_PAREN] = interpret_paren,
    [AT_REDIRECT] = interpret_redirect,
    [AT_PIPELINE] = interpret_pipe,
    [AT_OR] = interpret_or,
    [AT_AND] = interpret_and,
    [AT_ARGUMENT] = interpret_argument
};

int interpret(const ast_t *ast, shell_t *shell)
{
    if (!ast)
        return 84;
    if (interpret_functions[ast->type] == NULL) {
        dprintf(2, "Programmer error! Unimplemented type %hhu\n", ast->type);
        return 84;
    }
    return interpret_functions[ast->type](ast, shell);
}

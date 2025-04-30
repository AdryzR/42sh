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
    [AT_PIPE] = interpret_pipe,
    [AT_OR] = interpret_or,
    [AT_AND] = interpret_and,
    [AT_ARGUMENT] = interpret_argument
};
static int interpret_error(UNUSED const ast_t *ast, UNUSED shell_t *shell)
{
    dprintf(2, "Syntax error in AST\n");
    return 84;
}
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

int interpret_error(UNUSED const ast_t *ast, UNUSED shell_t *shell)
{
    dprintf(2, "Syntax error in AST\n");
    return 84;
}

int interpret_program(const ast_t *ast, shell_t *shell)
{
    int status = 0;

    for (size_t i = 0; i < ast->data.program.count; i++) {
        status = interpret(ast->data.program.data[i], shell);
    }
    if (status != 0)
        shell->shell_status = 84;
    return status;
}

int interpret_argument(const ast_t *ast, shell_t *shell)
{
    size_t array_size;

    if (!shell->command) {
        shell->command = calloc(2, sizeof(char *));
        if (!shell->command)
            return 84;
        shell->command[0] = strdup(ast->data);
        return 0;
    }
    array_size = len_array(shell->command);
    shell->command = reallocarray(
        shell->command, array_size + 2, sizeof(char *)
    );
    shell->command[array_size] = strdup(ast->data);
    shell->command[array_size + 1] = NULL;
    return 0;
}

int interpret_command(const ast_t *ast, shell_t *shell)
{
    int status;

    for (size_t i = 0; i < ast->data.command.count; i++)
        interpret(ast->data.command.data[i], shell);
    ;
    shell->line = strdup(shell->command[0]);
    status = check_shell_args(shell);
    ;
    free_array(shell->command);
    free(shell->line);
    shell->command = NULL;
    return status;
}

/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_paren
*/

#include <interpreter.h>
#include <my_sh.h>

int interpret_paren(const ast_t *ast, shell_t *shell)
{
    int status = 0;
    pid_t pid = fork();
    int wstatus;

    if (pid < 0) {
        perror("fork");
        return 84;
    }
    if (pid == 0) {
        for (size_t i = 0; i < ast->data.paren.count; i++)
            status = interpret(ast->data.paren.data[i], shell);
        exit(status);
    }
    if (waitpid(pid, &wstatus, 0) < 0) {
        perror("waitpid");
        return 84;
    }
    return status;
}

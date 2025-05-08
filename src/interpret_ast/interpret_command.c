/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_command
*/

#include <interpreter.h>

/*
* Used after doing a redirection, make fd to base fd again and remove saves.
*/
static void cleanup_redir(shell_t *shell)
{
    for (int i = 0; i < 2; i++) {
        if (shell->saved_fds[i] < 0)
            continue;
        dup2(shell->saved_fds[i], i);
        close(shell->saved_fds[i]);
        shell->saved_fds[i] = -1;
    }
}

int interpret_command(const ast_t *ast, shell_t *shell)
{
    int status;

    for (size_t i = 0; i < ast->data.command.count; i++)
        interpret(ast->data.command.data[i], shell);
    ;
    shell->full_path = strdup(shell->command[0]);
    status = check_shell_args(shell);
    ;
    cleanup_redir(shell);
    free(shell->full_path);
    free_array(shell->command);
    shell->full_path = NULL;
    shell->command = NULL;
    return shell->shell_status;
}

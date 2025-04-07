/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** setup_left_redirections
*/

#include "my_sh.h"
#include <fcntl.h>

void make_left_to_right_red(shell_t *shell, char *filename, bool append)
{
    int file_fd = 0;
    int saved_stdout = dup(STDOUT);

    filename = strip_str(filename, ' ');
    file_fd = open(filename, O_WRONLY | O_CREAT |
        (append ? O_APPEND : O_TRUNC), 0664);
    dup2(file_fd, STDOUT);
    check_shell_args(shell);
    dup2(saved_stdout, STDOUT);
    close(file_fd);
    close(saved_stdout);
    free(filename);
}

bool is_ltr_red(shell_t *shell)
{
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '>')
            return true;
    return false;
}

bool is_double_ltr_red(shell_t *shell)
{
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '>' && shell->line[i + 1] &&
            shell->line[i + 1] == '>')
                return true;
    return false;
}

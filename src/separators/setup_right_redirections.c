/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** setup_right_directions
*/

#include "my_sh.h"
#include <fcntl.h>

void make_right_to_left_red(shell_t *shell, char *filename)
{
    int file_fd = 0;
    int saved_stdin = dup(STDIN);

    filename = strip_str(filename, ' ');
    file_fd = open(filename, O_RDONLY, 0664);
    dup2(file_fd, STDIN);
    close(file_fd);
    check_shell_args(shell);
    dup2(saved_stdin, STDIN);
    close(saved_stdin);
    free(filename);
}

bool is_rtl_red(shell_t *shell)
{
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '<')
            return true;
    return false;
}

bool is_double_rtl_red(shell_t *shell)
{
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '<' && shell->line[i + 1] &&
            shell->line[i + 1] == '<')
                return true;
    return false;
}

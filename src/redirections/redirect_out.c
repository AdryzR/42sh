/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** left_redirect
*/

#include <my_sh.h>
#include <fcntl.h>
#include <parser.h>

int make_redirect_out(shell_t *shell, char *filename, redir_type_t type)
{
    int file_fd = 0;
    int saved_stdout = dup(STDOUT);

    file_fd = open(filename, O_WRONLY | O_CREAT |
        (REDIR_APPEND ? O_APPEND : O_TRUNC), 0664);
    dup2(file_fd, STDOUT);
    return 0;
}

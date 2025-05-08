/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** left_redirect
*/

#include <my_sh.h>
#include <fcntl.h>
#include <parser.h>
#include <errno.h>

int make_redirect_out(shell_t *shell, char *filename, redir_type_t type)
{
    int file_fd = 0;
    int saved_stdout = dup(STDOUT);

    file_fd = open(filename, O_WRONLY | O_CREAT |
        (type == REDIR_APPEND ? O_APPEND : O_TRUNC), 0664);
    if (file_fd < 0) {
        dprintf(2, "%s: %s.\n", filename, strerror(errno));
        return 84;
    }
    dup2(file_fd, STDOUT);
    close(file_fd);
    return 0;
}

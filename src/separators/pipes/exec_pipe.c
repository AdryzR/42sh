/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** exec_pipe
*/

#include "my_sh.h"
#include <unistd.h>

static void dup_and_close(int fd, int fd2)
{
    dup2(fd, fd2);
    close(fd);
}

int exec_pipe(shell_t *shell, char **commands)
{
    int pipefd[2];
    int original_fd[2] = { dup(0), dup(1) };

    if (original_fd[0] < 0 || original_fd[1] < 0)
        return 84;
    shell->should_skip_wait = true;
    for (int i = 0; i < shell->nb_pipes; i++) {
        if (pipe(pipefd) != 0)
            return 84;
        dup_and_close(pipefd[1], STDOUT);
        shell->line = commands[i];
        handle_redirections(shell);
        dup_and_close(pipefd[0], STDIN);
    }
    shell->should_skip_wait = false;
    dup_and_close(original_fd[STDOUT], STDOUT);
    shell->line = commands[shell->nb_pipes];
    shell->shell_status = handle_redirections(shell);
    dup_and_close(original_fd[STDIN], STDIN);
    return 1;
}

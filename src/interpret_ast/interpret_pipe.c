/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_pipe
*/

#include <interpreter.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

static void dup_and_close(int fd, int fd2)
{
    dup2(fd, fd2);
    close(fd);
}

int interpret_pipe(const ast_t *ast, shell_t *shell)
{
    int pipefd[2];
    int original_fd[2] = { dup(0), dup(1) };

    if (original_fd[0] < 0 || original_fd[1] < 0)
        return 84;
    shell->should_skip_wait = true;
    for (size_t i = 0; i < ast->data.pipeline.count - 1; i++) {
        if (pipe(pipefd) != 0)
            return 84;
        dup_and_close(pipefd[1], STDOUT);
        interpret(ast->data.pipeline.data[i], shell);
        dup_and_close(pipefd[0], STDIN);
    }
    shell->should_skip_wait = false;
    dup_and_close(original_fd[STDOUT], STDOUT);
    interpret(ast->data.pipeline.data[ast->data.pipeline.count - 1], shell);
    dup_and_close(original_fd[STDIN], STDIN);
    return 0;
}

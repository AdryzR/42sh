/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** heredoc_redirect
*/

#include <my_sh.h>
#include <fcntl.h>
#include <parser.h>

// TODO: change pipe() by using a temporary file to avoid blocking pipes.
int make_redir_heredoc(shell_t *shell, const char *eof)
{
    int pipefd[2];
    ssize_t bytes_read = 0;
    char *line = NULL;
    size_t len = 0;

    pipe(pipefd);
    bytes_read = getline(&line, &len, stdin);
    while (bytes_read > 0) {
        if (strstr(line, eof) == line && line[strlen(eof)] == '\n')
            break;
        write(pipefd[1], line, bytes_read);
        bytes_read = getline(&line, &len, stdin);
    }
    close(pipefd[1]);
    dup2(pipefd[0], STDIN);
    close(pipefd[0]);
    free(line);
    return 0;
}

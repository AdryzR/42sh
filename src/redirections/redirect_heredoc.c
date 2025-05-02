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
int make_redir_heredoc(shell_t *shell, char *eof)
{
    int pipefd[2];
    ssize_t bytes_read = 0;
    char *line = NULL;
    size_t len = 0;

    pipe(pipefd);
    do {
        bytes_read = getline(&line, &len, stdin);
        if (strstr(line, eof) == line && line[strlen(eof)] == '\n')
            break;
        write(pipefd[1], line, bytes_read);
    } while (bytes_read != -1);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN);
    close(pipefd[0]);
    free(line);
    return 0;
}

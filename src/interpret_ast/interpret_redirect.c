/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** interpret_redirect
*/

#include <interpreter.h>
#include <my_sh.h>

int interpret_redirect(const ast_t *ast, shell_t *shell)
{
    int status = 0;
    const redir_node_t *redir = &ast->data.redirect;

    if (is_left_redir(redir->red_type)) {
        shell->saved_fds[STDOUT] = dup(STDOUT);
        status = make_redirect_out(shell, redir->path, redir->red_type);
    } else {
        shell->saved_fds[STDIN] = dup(STDIN);
        if (redir->red_type == REDIR_HEREDOC)
            status = make_redir_heredoc(shell, redir->path);
        else
            status = make_redirect_in(shell, redir->path);
    }
    return status;
}

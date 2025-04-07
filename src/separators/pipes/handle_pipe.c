/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle_pipe
*/

#include "my_sh.h"

static int err_invalid_command(char **commands, shell_t *shell)
{
    my_putstr_ch(2, "Invalid null command.\n");
    free_array(commands);
    return ret_and_set_status(84, shell);
}

static bool is_a_pipe(shell_t *shell)
{
    if (!shell->line)
        return true;
    for (int i = 0; shell->line[i]; i++)
        if (shell->line[i] == '|')
            return true;
    return false;
}

int check_pipes(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, "|");
    int ret = 0;

    if (commands == NULL)
        return 84;
    if (!commands[1] && is_a_pipe(shell))
        return err_invalid_command(commands, shell);
    if (shell->nb_pipes > 0)
        ret = exec_pipe(shell, commands);
    free(commands);
    return ret;
}

int handle_pipes(shell_t *shell)
{
    if (check_pipes(shell) == 1)
        return shell->shell_status;
    return handle_redirections(shell);
}

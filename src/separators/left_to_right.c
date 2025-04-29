/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** left_to_right
*/

#include <sys/stat.h>
#include <fcntl.h>
#include "my_sh.h"

int left_to_right(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, ">");

    if (len_array(commands) > 2)
        return ambiguous_redirect_err(commands, shell, OUTPUT);
    if (!commands[1] && is_ltr_red(shell))
        return missing_name_err(commands, shell);
    if (commands[1] != NULL) {
        shell->line = commands[0];
        make_left_to_right_red(shell, commands[1], false);
        free_array(commands);
        return 1;
    }
    free_array(commands);
    return 0;
}

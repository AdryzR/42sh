/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** double_left_to_right
*/

#include "my_sh.h"
#include <fcntl.h>

static bool is_ltr_simple_red(char *line)
{
    for (int i = 0; line[i]; i++)
        if (line[i] == '>')
            return true;
    return false;
}

int double_left_to_right(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, ">>");

    if (len_array(commands) > 2)
        return ambiguous_redirect_err(commands, shell, OUTPUT);
    if (len_array(commands) == 2 && is_ltr_simple_red(commands[1]))
        return missing_name_err(commands, shell);
    if (commands[1] != NULL) {
        shell->line = commands[0];
        make_left_to_right_red(shell, commands[1], true);
        free_array(commands);
        return 1;
    }
    return 0;
}

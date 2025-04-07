/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** check_double_r_to_l_errors
*/

#include "my_sh.h"

static bool is_another_r_to_l_redirect(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '<')
            return true;
    return false;
}

int check_double_r_to_l_errors(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, "<<");
    char **second_array = NULL;

    if (len_array(commands) > 2)
        return ambiguous_redirect_err(commands, shell, INPUT);
    for (int i = 0; commands[i]; i++)
        if (len_array(commands) == 2 &&
            is_another_r_to_l_redirect(commands[i]))
                return ambiguous_redirect_err(commands, shell, INPUT);
    return 0;
}

/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** check_l_to_r_errors
*/

#include "my_sh.h"

/* return true if another '>' is found, then implictly handles ">>" case.*/
static bool is_another_dbl_l_to_r_redirect(char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] == '>')
            return true;
    return false;
}

int check_l_to_r_errors(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, ">");

    if (len_array(commands) > 2)
        return ambiguous_redirect_err(commands, shell, OUTPUT);
    for (int i = 0; commands[i]; i++)
        if (is_another_dbl_l_to_r_redirect(commands[i]))
            return ambiguous_redirect_err(commands, shell, OUTPUT);
    free_array(commands);
    return 0;
}

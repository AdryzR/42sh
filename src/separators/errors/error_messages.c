/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** error_messages
*/

#include "my_sh.h"

/* Return and set status to 84 + print error message based on the redirection
    type. (for '>' signs, use output, for '<' use input) !*/
int ambiguous_redirect_err(char **commands, shell_t *shell, int type)
{
    my_putstr_ch(2, (type == OUTPUT) ? "Ambiguous output redirect.\n" :
        "Ambiguous input redirect.\n");
    free_array(commands);
    return ret_and_set_status(84, shell);
}

int missing_name_err(char **commands, shell_t *shell)
{
    my_putstr_ch(2, "Missing name for redirect.\n");
    free_array(commands);
    return ret_and_set_status(84, shell);
}

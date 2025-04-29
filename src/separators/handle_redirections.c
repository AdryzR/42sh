/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** Handle left to right redirection
*/

#include "my_sh.h"

int check_redirections_error(shell_t *shell)
{
    int (*ret[])(shell_t *) = {check_double_l_to_r_errors,
        check_l_to_r_errors, check_double_r_to_l_errors, check_r_to_l_errors};
    int result = 0;

    for (int i = 0; i < 4; i++) {
        result = ret[i](shell);
        if (result == 84)
            return result;
    }
    return 0;
}

static int right_to_left(shell_t *shell)
{
    char **commands = str_to_warray(shell->line, "<");

    if (len_array(commands) > 2)
        return ambiguous_redirect_err(commands, shell, INPUT);
    if (!commands[1] && is_rtl_red(shell))
        return missing_name_err(commands, shell);
    if (commands[1] != NULL) {
        shell->line = commands[0];
        make_right_to_left_red(shell, commands[1]);
        free_array(commands);
        return 1;
    }
    free_array(commands);
    return 0;
}

int handle_redirections(shell_t *shell)
{
    int (*handlers[])(shell_t *) = {check_redirections_error,
        double_left_to_right, left_to_right, right_to_left};
    int ret = 0;

    for (int i = 0; i < 4; i++) {
        ret = handlers[i](shell);
        if (ret == 84)
            return ret;
        if (ret == 1)
            return shell->shell_status;
    }
    return check_shell_args(shell);
}

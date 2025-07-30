/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_repeat.c
*/

#include "my_sh.h"
#include "parser.h"
#include "interpreter.h"

static void repeat_loop(int n, shell_t *shell)
{
    char **args = shell->command;

    shell->command = shell->command + 2;
    for (int i = 0; i < n; i++)
        check_shell_args(shell);
    shell->command = args;
}

static int manage_error(shell_t *shell)
{
    if (!shell->command[1] || !shell->command[2]) {
        shell->shell_status = 1;
        my_putstr_ch(2, "repeat: Too few arguments.\n");
        return 84;
    }
    if (my_str_isnum(shell->command[1]) == 0) {
        shell->shell_status = 1;
        my_putstr_ch(2, "repeat: Badly formed number.\n");
        return 84;
    }
    return 0;
}

int my_repeat(shell_t *shell)
{
    int n = 0;
    int k = 0;

    if (manage_error(shell) == 84)
        return 84;
    n = my_getnbr(shell->command[1]);
    repeat_loop(n, shell);
    return 0;
}

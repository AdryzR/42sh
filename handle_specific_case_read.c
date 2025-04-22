/*
** EPITECH PROJECT, 2025
** 42sh_trop_banger
** File description:
** handle_specific_case_read
*/

#include "my.h"
#include "my_sh.h"

int init_output(shell_t *shell, struct termios *newt, struct termios *oldt)
{
    if (!shell)
        return 84;
    if (isatty(STDIN_FILENO))
        my_putstr("> ");
    newt = oldt;
    newt->c_lflag &= ~(ICANON | ECHO);
}

int specific_case(shell_t *shell, char c, char *line)
{
    if (arrows_key(shell, shell->history, c) == 0)
        return 1;
    return 0;
}

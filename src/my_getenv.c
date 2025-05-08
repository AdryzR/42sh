/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_getenv
*/

#include "my_sh.h"

char *my_getenv(shell_t *shell, char *tofind)
{
    envi_t *line = shell->envi;

    for (line = shell->envi; line && strcmp(line->parts[0], tofind) != 0;
        line = line->next);
    if (!line)
        return NULL;
    return line->parts[1];
}

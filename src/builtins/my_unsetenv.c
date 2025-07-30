/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_unsetenv
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

bool is_head(envi_t *current)
{
    return !current->prev;
}

void delete_env_node(envi_t *current, shell_t *shell)
{
    if (!current)
        return;
    free(current->env);
    for (int i = 0; current->parts[i]; i++)
        free(current->parts[i]);
    free(current->parts);
    if (current->prev)
        current->prev->next = current->next;
    if (current->next)
        current->next->prev = current->prev;
    if (is_head(current))
        shell->envi = current->next;
    free(current);
}

static int check_unsetenv_args(shell_t *shell)
{
    if (shell->nb_args != 2)
        return 84;
    return 0;
}

int my_unsetenv(shell_t *shell)
{
    envi_t *buff = shell->envi;

    if (check_unsetenv_args(shell) == 84)
        return 84;
    for (; buff && my_strcmp(buff->parts[0], shell->command[1]) != 0;
        buff = buff->next);
    if (!buff)
        return 84;
    delete_env_node(buff, shell);
    return 0;
}

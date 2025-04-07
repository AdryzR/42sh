/*
** EPITECH PROJECT, 2025
** minishell1
** File description:
** my_env
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "my_printf.h"
#include "my_sh.h"

int my_env(shell_t *shell)
{
    envi_t *buff = shell->envi;

    for (; buff; buff = buff->next)
        my_printf("%s\n", buff->env);
    return 0;
}

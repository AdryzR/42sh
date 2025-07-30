/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_env
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "printf.h"
#include "my_sh.h"

int my_env(shell_t *shell)
{
    envi_t *buff = shell->envi;

    for (; buff; buff = buff->next)
        printf("%s\n", buff->env);
    return 0;
}

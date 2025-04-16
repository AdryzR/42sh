/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbling
*/

#include "my.h"
#include "my_printf.h"
#include "my_sh.h"
#include <glob.h>
#include <stdio.h>

char **globbing(char *pattern)
{
    glob_t res;

    if (!pattern)
        return NULL;
    if (glob(pattern, 0, NULL, &res) != 0)
        return NULL;
    return res.gl_pathv;
}

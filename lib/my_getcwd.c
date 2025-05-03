/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** my_getcwd
*/

#include <my_sh.h>

char *my_getcwd(void)
{
    static char path[SH_PATH_MAX];

    return getcwd(path, SH_PATH_MAX) ?: "";
}

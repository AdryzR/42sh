/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** print_prompt
*/

#include <my_sh.h>

void print_prompt(void)
{
    char path[SH_PATH_MAX];

    if (getcwd(path, SH_PATH_MAX) != NULL)
        printf("%s> ", path);
    else
        fputs("> ", stdout);
}

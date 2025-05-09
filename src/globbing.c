/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbling
*/

#include "my.h"
#include "my_sh.h"
#include <glob.h>
#include <stdio.h>

glob_t globbing(char *pattern)
{
    glob_t res;

    if (!pattern)
        return (glob_t){ 0 };
    if (glob(pattern, 0, NULL, &res) != 0) {
        globfree(&res);
        return (glob_t){ 0 };
    }
    return res;
}

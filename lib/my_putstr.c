/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** my_putstr
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
    return 0;
}

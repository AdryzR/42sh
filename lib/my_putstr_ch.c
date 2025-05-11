/*
** EPITECH PROJECT, 2025
** Sudo
** File description:
** my_putstr_ch
*/

#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int my_putstr_ch(int fd, char const *str)
{
    write(fd, str, my_strlen(str));
    return 0;
}
